#!/bin/sh

# mkfile c test "stdio.h stdlib.h" "void test(int a)" "void fun(char* s, int n)"
# mkfile sh test 3

if [ $# -lt 1 ]; then
  exit 1
fi

# Creating c files
if [ $1 = 'c' ]; then
  if [ $# -lt 2 ]; then
    exit 1
  fi

  name="$2.$1"
  touch $name
  echo "File created!"
  echo "/* $name */"        >> $name
  echo                      >> $name

  for inc in $3; do
    echo "#include <$inc>"  >> $name
  done
  echo >> $name
  echo >> $name
  echo "#include created!"

  shift; shift; shift

  while [ -n "$1" ]; do
    echo "$1"               >> $name
    echo "{"                >> $name
    echo "  "               >> $name
    echo ""                 >> $name
    echo "  return;"        >> $name
    echo "}"                >> $name
    echo ""                 >> $name
    shift
  done
  echo "Functions created!"

  echo "int main()"         >> $name
  echo "{"                  >> $name
  echo "  "                 >> $name
  echo ""                   >> $name
  echo "  return 0;"        >> $name
  echo "}"                  >> $name
  echo "Main created!"

  vim $name

fi
