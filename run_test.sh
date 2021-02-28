#!/bin/bash
set -e

# Build bin/c_compiler 
make clean
make

# Compile test program using bin/c_compiler
bin/c_compiler -S test.c -o test.s 2>/dev/null >test.s
# Assemble generated assembly code via gcc
mips-linux-gnu-gcc -mfp32 -o test.o -c test.s
# Link to main function and generate executable via gcc
mips-linux-gnu-gcc -mfp32 -static -o test test.o test_driver.c

# run executable on qemu-mips
set +e 
qemu-mips test 
if [ $? -eq 0 ]
  then
    echo ✅ pass
    exit 0
  else
    echo ❌ fail
    exit 1
fi
