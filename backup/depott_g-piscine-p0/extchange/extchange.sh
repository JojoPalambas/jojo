#/bin/sh

if [ $# -lt 2 ]; then
	echo $'Usage: extchange.sh \'ext1\' \'ext2\''
	exit 1
fi

if [ $# -gt 2 ]; then
	echo $'Usage: extchange.sh \'ext1\' \'ext2\''
	exit 1
fi

files="*.$1"

if [ $files = '*.'$1 ]; then
	exit 2
fi

for file in $files; do
	fil=$(cut -d '.' -f1 <<< $file)
	echo mv "$fil".$1 "$fil".$2
	mv "$fil".$1 "$fil".$2
done
