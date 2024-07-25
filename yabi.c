#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>

#define NUM_CELLS 30000

void interpretBF(const char *input, char cells[NUM_CELLS], int cursorPos) {
    size_t inputLen = strlen(input);
    for (size_t inputPos = 0; inputPos < inputLen; inputPos++) {
        switch (input[inputLen]) {
            case '>':
                if (cursorPos == NUM_CELLS-1) {
                    cursorPos = 0;
                } else {
                    cursorPos++;
                }
                break;
            case '<':
                if (cursorPos == 0) {
                    cursorPos = NUM_CELLS-1;
                } else {
                    cursorPos--;
                }
                break;
            case '+':
                cells[cursorPos]++;
                break;
            case '-':
                cells[cursorPos]--;
                break;
            case '.':
                putchar(cells[cursorPos]);
                break;
            case ',':
                cells[cursorPos] = getchar();
                break;
            case '[':
                interpretBF(input + inputPos, cells, cursorPos);
                break;
            case ']':
                return;
                break;
        }
    }
}

struct SyntaxError {
    size_t col;
    size_t line;
    long int bracket;
};

void checkBracketSyntax(const char *input, struct SyntaxError *se) {
    size_t inputLen = strlen(input);
    for (size_t inputPos = 0; inputPos < inputLen; inputPos++) {
        printf("%c", input[inputLen]);
        switch(input[inputLen]) {
            case '[':
                puts("flakdjs");
                se->bracket++;
                checkBracketSyntax(input + inputLen, se);
                break;
            case ']':
                return;
                break;
            case '\n':
                se->line++;
                break;
            default:
                se->col++;
                break;
        }
    }
    return;
}


int readToInterpreter(FILE *fp) {
    char *input = malloc(sizeof(char) * 1);
    size_t stringLen = 1;
    char ch;

    while ((ch = fgetc(fp)) != EOF) {
        input = realloc(input, sizeof(char) * (stringLen + 1));
        input[stringLen - 1] = ch;
        stringLen++;
    }
    input[stringLen] = '\0';
    printf("%s: %ld\n", input, strlen(input));

    struct SyntaxError se = {
        .col = 0,
        .line = 0,
        .bracket = 0,
    };

    checkBracketSyntax(input, &se);
    printf("line: %ld, col: %ld, bracket: %ld", se.line, se.col, se.bracket);
    if (se.bracket > 0) {
        printf("syntax error: unclosed bracket in line %ld column %ld",
                se.line,
                se.col);
    } else if (se.bracket < 0) {
        printf("syntax error: unexpected closing bracket in line %ld column %ld",
                se.line,
                se.col);

    }

    interpretBF(input, (char[NUM_CELLS]){ 0 }, 0);

    free(input);
    return 1;
}

int main(int argc, char *argv[]) {
    if (isatty(STDIN_FILENO)) {
        if (argc < 2) {
            puts("missing file argument, aborting...");
            return EXIT_FAILURE;
        } else {
            for (int i = 1; i < argc; i++) {
                FILE *fp = fopen(argv[i], "r");
                if (!fp) {
                    printf("%s: failed to open file, aborting...\n", argv[i]);
                    return EXIT_FAILURE;
                }
                if (!readToInterpreter(fp)) {
                    fclose(fp);
                    return EXIT_FAILURE;
                }
                fclose(fp);
            }
        }
    } else {
        if (!readToInterpreter(stdin)) {
            return EXIT_FAILURE;
        }
    }
    return EXIT_SUCCESS;
}
