.PHONY = clean build

CC        = gcc
SRC       = yabi.c
CFLAGS    = -std=c17 -Wpedantic -Wall -Werror -Wextra -O3
#SANITIZER = -fsanitize=address -fsanitize=undefined
BIN       = yabi

build:
	$(CC) $(SRC) $(CFLAGS) $(SANITIZER) -o $(BIN)

clean:
	rm $(BIN)
