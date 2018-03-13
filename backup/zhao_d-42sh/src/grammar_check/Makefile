CPPFLAGS=-DDEBUG_UNIT
CC=gcc
CFLAGS=-Wall -Werror -Wextra -pedantic -g  -std=c99
LDLIBS=
LDFLAGS=

SRC=grammar_check.c
OBJ=${SRC:.c=.o}

all:grammar_check

grammar_chec:${OBJ}

clean:
	${RM} ${OBJ} grammar_check
