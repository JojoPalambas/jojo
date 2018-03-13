#!/bin/sh

for var in $*; do
	if [ ! -e $var ]; then
		echo $var does not exist
	elif [ -d $var ]; then
		echo "$var: directory"
	elif [ -f $var ]; then
		echo "$var: file"
	else
		echo "$var: unknown"
	fi
done
