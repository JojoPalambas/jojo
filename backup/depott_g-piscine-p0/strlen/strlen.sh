#!/bin/sh

if [ $# -lt 1 ]; then
	exit 1
fi

for word in $*; do
	nb=$(wc -m <<<$word)
	nb=$((nb - 1))
	if [ $nb -lt 2 ]; then
		echo "\"$word\" counts $nb character"
	else
		echo "\"$word\" counts $nb characters"
	fi
done

exit 0
