#include <stdio.h>
#include <stdlib.h>
#include <math.h>

enum
{
    OCT_BASE = 8,
    BITS_AMOUNT = 3
};

int
main(int argc, char *argv[])
{
    const char* rwx = "rwx";

    for (int i = 0; i < argc - 1; i++) {
        int current_number = 0;
        sscanf(argv[i + 1], "%o", &current_number);

        for (int j = BITS_AMOUNT - 1; j >= 0; j--) {
            int digit = (int) ((double) current_number / (double) (1 << (j * 3))) % OCT_BASE;

            for (int k = BITS_AMOUNT - 1; k >= 0; k--) {
                if (digit & (1 << k)) {
                    printf("%c", rwx[BITS_AMOUNT - 1 - k]);
                }
                else {
                    printf("-");
                }
            }
        }
        printf("\n");
    }

    return 0;
}
