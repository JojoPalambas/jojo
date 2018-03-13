CC = gcc
CFLAGS = -std=c99 -Wall -Wextra -Werror -pedantic -g
LDLIBS = -lm

EXEC = rt
OBJ = llist.o parsing.o vector3.o out.o image.o

.PHONY: all clean

all: $(EXEC)

$(EXEC): $(OBJ)

clean:
	${RM} $(EXEC)
	${RM} $(OBJ)
