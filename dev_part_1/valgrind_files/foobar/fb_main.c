
/*--------------------------------------------------------------------*/
/*--- Nulgrind: The minimal Valgrind tool.               fb_main.c ---*/
/*--------------------------------------------------------------------*/

/*
   This file is part of Nulgrind, the minimal Valgrind tool,
   which does no instrumentation or analysis.

   Copyright (C) 2002-2017 Nicholas Nethercote
      njn@valgrind.org

   This program is free software; you can redistribute it and/or
   modify it under the terms of the GNU General Public License as
   published by the Free Software Foundation; either version 2 of the
   License, or (at your option) any later version.

   This program is distributed in the hope that it will be useful, but
   WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, see <http://www.gnu.org/licenses/>.

   The GNU General Public License is contained in the file COPYING.
*/

#include "pub_tool_basics.h"
#include "pub_tool_tooliface.h"
#include "pub_tool_options.h"


static ULong total_instructions = 0;
static VG_REGPARM(0) void incement_count(void) { total_instructions++; }

static void fb_post_clo_init(void)
{
   /* Unless we are actually tracking file descriptors we act as if we don't
      handle any errors.  */
   if (!VG_(clo_track_fds))
     VG_(needs_core_errors)(False);
}

static
IRSB* fb_instrument ( VgCallbackClosure* closure,
                      IRSB* bb,
                      const VexGuestLayout* layout, 
                      const VexGuestExtents* vge,
                      const VexArchInfo* archinfo_host,
                      IRType gWordTy, IRType hWordTy )
{
   
   IRSB *bb_out = deepCopyIRSBExceptStmts(bb);
   Int ii;

   for (ii = 0; ii < bb->stmts_used; ii++) {
      IRStmt *ir_statement = bb->stmts[ii];
      if (!ir_statement)
         continue;

      // Copy statement to output block
      addStmtToIRSB(bb_out, ir_statement);

      // Instrumentation: count the instruction at Ist_IMark
      if (ir_statement->tag == Ist_IMark) {
         IRDirty *dirty_statament = unsafeIRDirty_0_N(
            0, "incement_count",
            VG_(fnptr_to_fnentry)(&incement_count), mkIRExprVec_0());
         addStmtToIRSB(bb_out, IRStmt_Dirty(dirty_statament));
      }
   }

  return bb_out;
}

static void fb_fini(Int exitcode)
{
   VG_(umsg)
  ("Total number of instructions executed: %llu\n", total_instructions);
}

static void fb_pre_clo_init(void)
{
   VG_(details_name)            ("Countrind");
   VG_(details_version)         (NULL);
   VG_(details_description)     ("Profiling tool to count the number of executed instructions");
   VG_(details_copyright_author)(
      "Copyright (C) 2024, and GNU GPL'd, by Mushtaq Shaikh et al.");
   VG_(details_bug_reports_to)  (VG_BUGS_TO);

   VG_(details_avg_translation_sizeB) ( 275 );

   VG_(basic_tool_funcs)        (fb_post_clo_init,
                                 fb_instrument,
                                 fb_fini);
   VG_(needs_xml_output)        ();
   VG_(needs_core_errors)       (True); /* Yes, but... see fb_post_clo_init  */

   /* No needs, no core events to track */
}

VG_DETERMINE_INTERFACE_VERSION(fb_pre_clo_init)

/*--------------------------------------------------------------------*/
/*--- end                                                          ---*/
/*--------------------------------------------------------------------*/
