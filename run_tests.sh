#!/bin/bash
set -e 

TEST_DIR=${@: -1}
TEST_DIR=${TEST_DIR%*/} # remove the trailing "/"
TEST_ON_SUB_DIR=$1
NUM_TEST=0
NUM_PASS=0

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

function all_tests_in_one_direactory {
  for test_driver in "$1"/*_driver.c; do
    test=$(basename "${test_driver}")
    test=${test%_driver.c}
    NUM_TEST=$((NUM_TEST+1))

    ./run_test.sh "$1/${test}.c" 2 >"$1/${test}.output"
    exit_status=$?

    if (( ${exit_status} != 0 )); then
      printf "\033[0;31mfail\033[0m\t|%d\t\t|%s\n" "${exit_status}" "${test}"
    else
      printf "\033[0;32mpass\033[0m\t|%d\t\t|%s\n" "${exit_status}" "${test}"
      NUM_PASS=$((NUM_PASS+1))
    fi
  done
}

if [[ "${TEST_ON_SUB_DIR}" == "-r" ]]; then
  for sub_dir in "${TEST_DIR}"/*/; do
    sub_dir=${sub_dir%*/} # remove the trailing "/"
    echo "👇 ${sub_dir}"
    all_tests_in_one_direactory "${sub_dir}"
  done
else
  all_tests_in_one_direactory "${TEST_DIR}"
fi

printf "\n\n${NUM_PASS}/${NUM_TEST} tests pass\n"
