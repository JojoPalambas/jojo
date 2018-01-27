#!/bin/bash

ans='no'
message=""

while [ $ans != 'y' ]; do
    echo
    echo -n "First tag: "
    read action
    echo -n "Second tag: "
    read target
    echo -n "Main modification files: "
    read files
    echo -n "Commit message: "
    read comm
    message="[$action][$target] $files - $comm"

    echo
    echo "Your command will be:"
    echo "$ git add -A"
    echo "$ git commit -m \"$message\""
    echo
    echo -n "Are you sure you want this commit? (y/n) "
    read ans
    if [ ans = n ]; then
        echo "You have decided not to commit this message. You can re-edit it."
    else
        echo "Your commit will be done."
    fi
done

git add -A
git commit -m "$message"
