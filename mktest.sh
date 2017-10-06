#!/bin/sh

# mktest <number of files> <name> <extension> <content>

if [ $# -lt 4 ]; then
	echo 'mktest should be used like:'
	echo '        mktest <number of files> <name> <extension> <content>'
	echo 'Example ---> mktest 100 test txt "Ceci est un test"'
fi

if [ $# -gt 4 ]; then
	echo 'mktest should be used like:'
	echo '        mktest <number of files> <name> <extension> <content>'
	echo 'Example ---> mktest 100 test txt "Ceci est un test"'
fi

num=$1
name=$2
ext=$3
cont=$4

while [ $num -gt 0 ]; do
	wholename="$name$num.$ext"
	touch $wholename
	echo $cont > $wholename
	num=$((num - 1))
done
