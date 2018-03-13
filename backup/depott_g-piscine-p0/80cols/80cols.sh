#/bin/sh

if [ $# -lt 1 ]; then
	exit 1
fi

if [ $# -gt 1 ]; then
	exit 1
fi

if [ ! -f $1 ]; then
	exit 1
fi

if [ ! -r $1 ]; then
	exit 1
fi

IFS=$'\n'

var=$(cat $1)

for line in $var; do
	nb=$(wc -m <<< $line)
	if [ $nb -gt 80 ]; then
		echo $nb
	fi
done
