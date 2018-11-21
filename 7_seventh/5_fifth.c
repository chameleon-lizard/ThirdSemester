#include <stdlib.h>
#include <string.h>
#include <stdio.h>

enum
{
    WORD_INIT_SIZE = 8
};

int
main(void)
{
    int currentChar = 0;
    int maxLength = 0;
    char *longestWord = 0;

    while (1) {
        int length = 0;
        char *currentWord = calloc(WORD_INIT_SIZE, sizeof(*currentWord));
        int wordSize = 8;

        if (currentChar < 0x0010) {
            free(currentWord);
            break;
        }

        for(length = 0; (currentChar = fgetc(stdin)) > 0x0020; length++) {
            if (length == wordSize) {
                wordSize *= 2;
                currentWord = realloc(currentWord, wordSize);
            }
            currentWord[length] = currentChar;
        }

        if (length > maxLength) {
            longestWord = calloc(length, sizeof(*longestWord));
            memcpy(longestWord, currentWord, length * sizeof(*longestWord));
            maxLength = length;
            length = 0;
        }
        free(currentWord);
    }

    printf("\n%d\n", maxLength/2);

    for (int i = 0; i < maxLength; i++) {
        fputc(longestWord[i], stdout);
    }

    printf("\n");

    free(longestWord);

    return 0;
}
