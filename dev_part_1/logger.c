#include <stdio.h>
#include <stdint.h>

void LogBranch(int branchId, const char* filepath, int srcLine, int successor) {
    printf("br_%d\n",branchId);
    fflush(stdout);
}


void LogPointer(void (*funcPtr)()) {
    uintptr_t funcPtrValue = (uintptr_t)funcPtr;
    printf("*funcptr_%p\n", (void*)funcPtrValue);
}



