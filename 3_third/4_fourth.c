#include <stdio.h>
#include <limits.h>

int
main(void)
{
    char current_number = 0;
    char output[CHAR_BIT] = { 0 };
    int offset = 0;

    while (scanf("%hhx", &current_number) == 1) {
        for (int i = CHAR_BIT - 1; i >= 0; i--) {
            output[i] |= (current_number & 1) << offset;
            current_number >>= 1;
        }

        if ((offset + 1) == CHAR_BIT) {
            for (int i = CHAR_BIT - 1; i >= 0; i--) {
                printf("%hhx ", output[i]);
                output[i] = 0;
            }
            printf("\n");
            offset = -1;
        }
        offset++;
    }

    return 0;
}
