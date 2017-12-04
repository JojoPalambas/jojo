CC = gcc
CFLAGS = -std=c99 -Wall -Wextra -Werror -pedantic -fPIC -D_GNU_SOURCE

VPATH = ./src

LIBOBJ = calloc.o free.o malloc.o realloc.o size.o
LIB = libmalloc.so

OBJ =
EXEC =

all: $(LIBOBJ)
	gcc -shared $(LIBOBJ) -o $(LIB)

test: all
	./tests/test.sh

clean:
	${RM} $(LIBOBJ)
	${RM} $(LIB)
