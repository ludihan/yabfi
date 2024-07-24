#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>

#define NUM_CELLS 30000

void interpretBF(FILE *fp) {
    size_t cursor = 0;
    size_t loopPos = -1;
    char cells[NUM_CELLS];

    char ch;
    char *src = malloc(sizeof(char) * 1);
    size_t srcLen = 0;
    while ((ch = fgetc(fp)) != EOF) {
        src = realloc(src, sizeof(char) * (srcLen + 1));
        src[srcLen] = ch;
        srcLen++;
    }

    for (size_t srcPos = 0; srcPos < srcLen; srcPos++) {
        puts("oi");
        switch (src[srcPos]) {
            case '>':
                if (cursor == NUM_CELLS-1) {
                    cursor = 0;
                } else {
                    cursor++;
                }
                break;
            case '<':
                if (cursor == 0) {
                    cursor = NUM_CELLS-1;
                } else {
                    cursor--;
                }
                break;
            case '+':
                cells[cursor]++;
                break;
            case '-':
                cells[cursor]--;
                break;
            case '.':
                putchar(cells[cursor]);
                break;
            case ',':
                cells[cursor] = getchar();
                break;
            case '[':
                cursor = loopPos;
                break;
            case ']':
                if (loopPos != (size_t)-1 || cells[cursor] != 0) {
                    cursor = srcPos;
                }
                break;
        }
        printf("cursor: %ld\n", cursor);
    }
    free(src);
}

int main(int argc, char *argv[]) {
    if (isatty(STDIN_FILENO)) {
        if (argc < 2) {
            puts("Missing file argument");
            return EXIT_FAILURE;
        } else {
            for (int i = 1; i < argc; i++) {
                FILE *fp = fopen(argv[i], "r");
                if (!fp) {
                    printf("%s: Failed to open file. Aborting...\n", argv[i]);
                    return EXIT_FAILURE;
                }
                interpretBF(fp);
                fclose(fp);
            }
        }
    } else {
        interpretBF(stdin);
    }
}
