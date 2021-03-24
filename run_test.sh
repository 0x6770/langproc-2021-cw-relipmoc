#!/bin/bash
set -e

TEST_FILE=$1
STANDALONE=${2:-1}

TEST=${TEST_FILE%.*}

# validate test target
if [[ -f ${TEST_FILE} ]]; then
  echo "Running test on \"${TEST_FILE}\""
  echo "========================="
else
  echo "${TEST_FILE} is not a file."
  exit 1
fi

# Build bin/c_compiler 
if [[ ${STANDALONE} == 1 ]]; then
  make clean
  make
fi

# Compile test program using bin/c_compiler
bin/c_compiler -S "${TEST_FILE}" -o "${TEST}".s 2>/dev/null
# Assemble generated assembly code via gcc
mips-linux-gnu-gcc -mfp32 -o "${TEST}".o -c "${TEST}".s
# Link to main function and generate executable via gcc
mips-linux-gnu-gcc -mfp32 -static -o "${TEST}".bin "${TEST}".o "${TEST}"_driver.c

# run executable on qemu-mips
set +e 
qemu-mips "${TEST}".bin
if (( $? == 0 )); then
  echo ✅ pass
  exit 0
else
  echo ❌ fail
  exit 1
fi
