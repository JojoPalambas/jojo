CC=gcc
CPPFLAGS= -MMD
CFLAGS= -Wall -Wextra -Werror -pedantic -std=c99 -g
LDLIBS= -lSDL2 -lSDL2_image -lm -lSDL2_mixer

OBJ= entities.o block.o map_operations.o parsemap.o display.o init.o  \
update.o inputs.o
DEP= entities.d block.d map_operations.d parsemap.d display.d init.d  \
update.d inputs.d

BIN= hardcore_bisounours

VPATH= src/

all: $(BIN)

$(BIN): $(OBJ)

-include $(DEP)

.PHONY: clean

clean:
	$(RM) $(OBJ) $(DEP) $(BIN) hardcore_bisounours.d
