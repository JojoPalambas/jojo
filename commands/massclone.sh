#!/bin/bash

for remote in $*; do
    git clone git@git.acu.epita.fr:$remote
done
