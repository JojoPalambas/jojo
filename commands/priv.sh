#!/bin/sh

if [ $# -lt 1 ]; then
    echo "Use: priv [OPTIONS AND FILES]"
    echo "Type 'priv -h' for more information"
    exit 1
fi

verbose=1
exp=1
path=~/git/jojo

for file in $*; do
    if [ $file = "-h" ]; then
        echo
        echo "------- HELP ------"
        echo
        echo "Use: priv [OPTIONS AND FILES]"
        echo
        echo "OPTIONS:"
        echo "          -h: help:       displays this help message"
        echo "          -v: verbose:    enables verbose mode (default)"
        echo "          -q: quiet:      disables verbose mode"
        echo "          -e: export:     enables export mode (default)"
        echo "          -i: import:     enables import mode"
        echo "          FILE:           exports/imports FILE to/from private"
        echo
        echo "--- END OF HELP ---"
        echo
    fi
done
