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
8. Check for the Mapping File generated in the current directory named "branch_info.txt"


