#!/bin/bash

for file in $(ls); do
    if ([ ! -e $file/$file.out ] || [ ! -e $file/$file.out ]); then
        vim $file/$file.tig
        vim $file/$file.out
        vim $file/$file.err
    fi
done
