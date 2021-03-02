#!/bin/bash
set -e 

TEST_DIR=$1

if [[ -d ${TEST_DIR} ]]; then
  echo "Running tests in \"${TEST_DIR}/\""
else 
  echo "Directory ${TEST_DIR} not found"
  exit 1
fi

echo 
echo "=============================="
echo "Building the compiler program"

make clean
if err_msg=$(make 2>&1 >/dev/null); then
  echo "${err_msg}"
fi

set +e

echo 
echo "=============================="
echo "Checking test cases"
echo -e "testcase\t|result\t|exit status"
echo "------------------------------"


for test in "${TEST_DIR}"/*.c; do
  ./run_test.sh "${test}" 2 >"${test}.output"
  exit_status=$?
  if (( ${exit_status} != 0 )); then
    printf "%s\t|%s\t|%d\n" "${test}" "fail" "${exit_status}"
  else
    printf "%s\t|%s\t|%d\n" "${test}" "pass" "${exit_status}"
  fi
done
