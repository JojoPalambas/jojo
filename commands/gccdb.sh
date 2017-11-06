#!/bin/sh

gcc -g -std=c99 -Wall -Wextra -Werror -pedantic  $1.c -o $1
