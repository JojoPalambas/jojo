#!/bin/bash

touch my_stdout
touch my_stderr
touch his_stdout
touch his_stderr
touch diff_out
touch diff_err

OK="\e[1;32m"
KO="\e[1;31m"
QU="\e[0;33m"
WH="\e[0;37m"

function test
{
    ./myfind $1 1> my_stdout 2> my_stderr
    find $1 1> his_stdout 2> his_stderr

    diff my_stdout his_stdout 1> diff_out 2>> diff_out
    if [ -z $(cat diff_out) ] 2> /dev/null; then
        out="stdout: [${OK}OK${WH}]"
    else
        out="stdout: [${KO}KO${WH}]"
    fi

    diff my_stderr his_stderr 1> diff_err 2>> diff_err
    if [ -z $(cat diff_err) ] 2> /dev/null; then
        err="stderr: [${OK}OK${WH}]"
    else
        err="stderr: [${KO}KO${WH}]"
    fi

    echo -e "-- Test for ${QU}\"$1\"${WH}:"
    echo -e "                                       $out    $err"
}

echo
echo ----- Beginning of the testsuite
echo

echo "--- Threshold 0"
echo

test ""
test "."
test "./"
test "tests"
test "./tests"
test "tests/test_dir"
test "tests/test.sh"
test "tests/test_*"
test "tests/*"
test "tests/test_dir/dir?"

echo
echo
echo "--- Threshold 1"
echo

test "-H tests"
test "-L tests"
test "-P tests"
test "tests/test_dir/dir2/lk"
test "-H tests/test_dir/dir2/lk"
test "-L -P tests"
test "-L -P -L tests"
test "tests -d"
test "-L tests -d"

echo
echo
echo "--- Threshold 2"
echo

test "tests -name dir1"
test "tests -name tests"
test "-name 'dir*'"
test "tests tests -name 'dir?'"
test "tests -name '*1*'"
test "tests -type d"
test "-type d"
test "tests -name '*1' -type d"
test "tests -name '*1' -type f"

echo
echo
echo "--- Threshold 3"
echo

test "tests -name '*1' -a -name 'f*'"
test "tests -name '*1' -o -name 'f*'"
test "-name 't*' -o -type f"

echo
echo "----- End of the testsuite"
echo

rm my_stdout
rm my_stderr
rm his_stdout
rm his_stderr
rm diff_out
rm diff_err
