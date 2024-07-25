.PHONY = clean build setup

CC        = cc
SRC       = $(wildcard src/*.c)
OBJ       = $(SRC:src/%.c=obj/%.o)
CFLAGS    = -std=c17 -Wpedantic -Wall -Werror -Wextra -O3
DEBUG     = -D DEBUG
#SANITIZER = -fsanitize=address -fsanitize=undefined
BIN       = yabi

build: setup $(OBJ)
	$(CC) $(OBJ) -o $(BIN) $(CFLAGS) $(DEBUG) $(SANITIZER)

setup:
	mkdir -p obj

obj/%.o: src/%.c
	$(CC) $< -c -o $@      $(CFLAGS) $(DEBUG) $(SANITIZER)

clean:
	rm $(OBJ)
	rm $(BIN)

