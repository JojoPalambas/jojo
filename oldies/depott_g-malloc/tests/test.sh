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
    LD_PRELOAD=./libmalloc.so $1 1> my_stdout 2> my_stderr
    $1 1> his_stdout 2> his_stderr

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

cd tests
make
cd ..

echo
echo ----- Beginning of the testsuite
echo

test "./test1"

echo
echo "----- End of the testsuite"
echo

cd tests
make clean
cd ..

rm my_stdout
rm my_stderr
rm his_stdout
rm his_stderr
rm diff_out
rm diff_err
