#include "yabi.h"

int main() {
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
                struct SyntaxError se = readToInterpreter(fp);
                if (se.bracket != 0) {
                    justifyError(&se, argv[i]);
                    fclose(fp);
                    return EXIT_FAILURE;
                }
                fclose(fp);
            }
        }
    } else {
        struct SyntaxError se = readToInterpreter(stdin);
        if (se.bracket != 0) {
            justifyError(&se, NULL);
            return EXIT_FAILURE;
        }
    }
    return EXIT_SUCCESS;
}
