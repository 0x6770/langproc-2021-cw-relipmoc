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
echo "------------------------------"
echo -e "result\t|exit status\t|test case"
echo "------------------------------"

for test_driver in "${TEST_DIR}"/*_driver.c; do
  test=$(basename "${test_driver}")
  test=${test%_driver.c}

  ./run_test.sh "${TEST_DIR}/${test}.c" 2 >"${TEST_DIR}/${test}.output"
  exit_status=$?

  if (( ${exit_status} != 0 )); then
    printf "\033[0;31mfail\033[0m\t|%d\t\t|%s\n" "${exit_status}" "${test}"
  else
    printf "\033[0;32mpass\033[0m\t|%d\t\t|%s\n" "${exit_status}" "${test}"
  fi
done
