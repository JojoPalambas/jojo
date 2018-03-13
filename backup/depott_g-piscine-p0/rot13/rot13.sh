#!/bin/sh

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

tr "a-zA-Z0-9" "n-za-mN-ZA-M5-90-4" < $1
