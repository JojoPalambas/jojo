#!/bin/sh

touch "AUTHORS"
echo "* depott_g" > AUTHORS
cat -e AUTHORS

if [ $# -lt 1 ]; then
	exit 0
fi

for option in $*; do
	if [ $option = '-r' ]; then
		touch "README"
	elif [ $option = '-t' ]; then
		touch "TODO"
	fi
done
