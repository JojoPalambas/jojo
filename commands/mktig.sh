#!/bin/bash

for file in $*; do
    mkdir $file
    vim $file/$file.tig
done
