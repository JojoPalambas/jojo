CC = gcc
CFLAGS = -std=c99 -Wall -Wextra -Werror -pedantic

VPATH = src
TESTPATH = tests

OBJ = accu.o my_string.o parse.o expr.o threshold0.o threshold1.o threshold2.o
EXEC = myfind

.PHONY: all test doc clean

all: $(EXEC)

$(EXEC): $(OBJ)

test: all
	./$(TESTPATH)/test.sh

doc:
	echo "The documentation is being written."

clean:
	${RM}	$(EXEC)
	${RM}	$(OBJ)
