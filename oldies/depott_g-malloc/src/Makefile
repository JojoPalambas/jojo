C = gcc
CFLAGS = -std=c99 -Wall -Wextra -Werror -pedantic -g -D_GNU_SOURCE

OBJ = malloc.o calloc.o realloc.o free.o size.o
EXEC = malloc

all: $(EXEC)

$(EXEC): $(OBJ)

clean:
	${RM} $(OBJ) $(EXEC)
