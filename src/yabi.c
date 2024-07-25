#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>

#define NUM_CELLS 30000

size_t interpretBF(const char *input, size_t inputLen, char cells[NUM_CELLS], int cursorPos) {
    for (size_t inputPos = 0; inputPos < inputLen; inputPos++) {
#ifdef DEBUG
#endif
        size_t offset = 0;
        switch (input[inputPos]) {
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
                offset = interpretBF(input + (inputPos + 1), inputLen - inputPos, cells, cursorPos);
                inputPos += offset + 1;
                break;
            case ']':
                return inputPos;
                break;
        }
    }
}

struct SyntaxError {
    size_t col;
    size_t line;
    long int bracket;
};

size_t checkBracketSyntax(const char *input, size_t inputLen, struct SyntaxError *se) {
    for (size_t inputPos = 0; inputPos < inputLen; inputPos++) {
#ifdef DEBUG
        printf("check: \"%s\" inputLen: %ld\nSyntaxError:\nline: %ld\ncol: %ld\nbracket: %ld\n\n",
                input,
                inputLen,
                se->col,
                se->line,
                se->bracket);
#endif
        size_t offset = 0;
        switch(input[inputPos]) {
            case '[':
                se->bracket++;
                se->col++;
                offset = checkBracketSyntax(input + 1, inputLen - inputPos + 1, se);
                inputPos += offset;
                break;
            case ']':
                se->bracket--;

                break;
            case '\n':
                se->line++;
            default:
                se->col++;
        }
    }
    return 0
}


struct SyntaxError readToInterpreter(FILE *fp) {
    char *input = malloc(sizeof(char) * 1);
    size_t stringLen = 1;
    char ch;

    while ((ch = fgetc(fp)) != EOF) {
        input = realloc(input, sizeof(char) * (stringLen + 1));
        input[stringLen - 1] = ch;
        stringLen++;
    }
    input[stringLen] = '\0';

    struct SyntaxError se = {
        .col = 0,
        .line = 0,
        .bracket = 0,
    };

    checkBracketSyntax(input, stringLen - 1, &se);
    if (se.bracket != 0) {
        interpretBF(input, stringLen - 1, (char[NUM_CELLS]){ 0 }, 0);
    }

    free(input);
    return se;
}

void justifyError(const struct SyntaxError *se, const char *file) {
    if (se->bracket > 0) {
        printf("%s: unclosed bracket at line %ld columns %ld, aborting...\n",
                (file != NULL ? file : (const char *)"stdin"),
                se->line,
                se->col);
    } else {
        printf("%s: unexpected closing bracket at line %ld columns %ld, aborting...\n",
                (file != NULL ? file : (const char *)"stdin"),
                se->line,
                se->col);
    }
}
