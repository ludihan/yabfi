.PHONY = clean build

CC        = gcc
SRC       = yabfi.c
CFLAGS    = -std=c17 -Wpedantic -Wall -Werror -Wextra -O3
#SANITIZER = -fsanitize=address -fsanitize=undefined
BIN       = yabfi

build:
	$(CC) $(SRC) $(CFLAGS) $(SANITIZER) -o $(BIN)

clean:
	rm yabfi
