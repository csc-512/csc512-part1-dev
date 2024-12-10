# Steps to compile and run the code for BranchTrace

1. Create a VCL Image "csc512_llvm" which has the LLVM installed 

2. Inside dev_part_1, run the following commands. This command builds your skeleton code

```bash

mkdir build

cd build

cmake ..

make

cd ..
```
3. Compile the logger.c file needed to log the branch and pointer trace

```bash
gcc -shared -o liblogger.so logger.c -fPIC
```

4. Compile the input test file "test1.c" using clang 

```bash
clang -fpass-plugin=`echo build/skeleton/SkeletonPass.*` -g test1.c -L. -llogger
```

5. Set the correct path 

```bash
 export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:.
```

6. run the executable binary for test1

```bash
./a.out
```

7. For the current test file "test1.c" you should see the following output on the terminal 

```
*funcptr_0x55c8738f7160

10

br_1

br_1

br_1

br_2
```
8. Check for the Mapping File generated in the current directory named "branch_info.txt". Below is the output of the "branch_info.txt" file.

```
br_1: test1.c, 12, 13
br_2: test1.c, 12, 15
```


10. To test the branch-trace pass with the Test Programs, use below commands and run the programs following the instructions on the terminal, if any user input is needed. 

```bash
clang -fpass-plugin=`echo build/skeleton/SkeletonPass.*` -g Test_Programs/contact_mgmt_small.c -L. -llogger

./a.out

clang -fpass-plugin=`echo build/skeleton/SkeletonPass.*` -g Test_Programs/encryption_small.c -L. -llogger

./a.out

clang -fpass-plugin=`echo build/skeleton/SkeletonPass.*` -g Test_Programs/segment_tree_large.c -L. -llogger

./a.out

clang -fpass-plugin=`echo build/skeleton/SkeletonPass.*` -g Test_Programs/bank_management_large.c -L. -llogger

./a.out

clang -fpass-plugin=`echo build/skeleton/SkeletonPass.*` -g Test_Programs/words_alphabetical_large.c -L. -llogger

./a.out
```

# Steps to download and run the Valgrind for Instruction Count

1. Download and install valgrind on the "csc512_llvm" machine using below commands.


```bash

git clone https://sourceware.org/git/valgrind.git

cd valgrind

./autogen.sh

./configure --prefix=<installation-directory>

make

make install

```

2. Modify the files within the valgrind home directory. First, modify the "configure.ac" file by adding below lines of code after the last "AC_CONFIG_FILES" entry.

```
AC_CONFIG_FILES([
    foobar/Makefile
    foobar/docs/Makefile
    foobar/tests/Makefile
])
```

3. Next, modify the "Makefile.am" in the valgrind home directory. Add below line of code in the "Tools" section after "none" 

```
none \
foobar
```

4. Copy the "foobar" directory available in this repo to the valgrind home directory. 

```bash
cp -rf dev_part_1/valgrind_files/foobar <valgrind_home_dir>
```

5. Re-compile and build the Valgrind directory using below commands

```bash
./autogen.sh

./configure --prefix=<installation-directory>

make

make install
```

6. Run the Valgrind on an executable to get the count of number of instructions executed.

```bash
<installation-directory>/bin/valgrind --tool=foobar <executable>
```

7. Here is an example run. I have installed the valgrind at the location "/home/mshaikh2/val_inst". I am using the executable "a.out" for the program test1.c available in the repo. 

```bash
/home/mshaikh2/val_inst/bin/valgrind --tool=foobar /home/mshaikh2/csc512-part1-dev/dev_part_1/a.out

```

8. Below if the output of the Valgring run on the test1.c executable. 

```
mshaikh2@vclvm179-45:~/csc512-part1-dev/dev_part_1$ /home/mshaikh2/val_inst/bin/valgrind --tool=foobar /home/mshaikh2/csc512-part1-dev/dev_part_1/a.out
==63486== Countrind, Profiling tool to count the number of executed instructions
==63486== Copyright (C) 2024, and GNU GPL'd, by Mushtaq Shaikh et al.
==63486== Using Valgrind-3.25.0.GIT and LibVEX; rerun with -h for copyright info
==63486== Command: /home/mshaikh2/csc512-part1-dev/dev_part_1/a.out
==63486== 
*funcptr_0x109160
10
br_1
br_1
br_1
br_2
==63486== 
==63486== Total number of instructions executed: 162248
```

# Test Programs

1. The folder Test_Programs contains a total of 5 Programs which are used to test this work. Out of the 5, 2 are small contrived programs, where names follows with the suffix "_small". The remaining 3 are complex programs from Github repository, where the name is followed by suffix "_large".

2. Below are the details of the source of the large complex test programs.

   Test_Programs/bank_management_large.c - https://github.com/AlgolRhythm/C-Bank-Management-Program/tree/master

   Test_Programs/segment_tree_large.c - https://github.com/TheAlgorithms/C/blob/master/data_structures/binary_trees/segment_tree.c

   Test_Programs/words_alphabetical_large.c - https://github.com/TheAlgorithms/C/blob/master/data_structures/binary_trees/words_alphabetical.c

3. The details of the small programs are mentioned below:

   Test_Programs/contact_mgmt_small.c - It is an interactive contact management system code.

   Test_Programs/encryption_small.c - It is a simple file encryption code which encrypt any given file. 
