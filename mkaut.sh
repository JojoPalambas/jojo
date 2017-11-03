#!/bin/sh

if [ $# -lt 1 ]; then
    exit 0
fi

for option in $*; do
    if [ $option = '-a' ]; then
        touch "AUTHORS"
        echo "* depott_g" > AUTHORS
        cat -e AUTHORS
    elif [ $option = '-r' ]; then
        touch "README"
        echo "[nothing done yet]" > README
    elif [ $option = '-t' ]; then
        touch "TODO"
        echo "[nothing planned yet]" > TODO
    elif [ $option = '-m' ]; then
        touch "Makefile"
    elif [ $option = '-tests' ]; then
        mkdir "tests"
    else
        echo "$option: option unknown"
    fi
done
