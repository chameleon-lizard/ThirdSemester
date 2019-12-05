#include <stdio.h>

enum
{
    ARG_AMOUNT = 2,
    RWX_LENGTH = 9
};

int
main(int argc, char *argv[])
{
    char rwx[10] = "xwrxwrxwr";
    if (argc < ARG_AMOUNT) {
        return 1;
    }

    for (int i = 1; i < argc; i++) {
        int buffer = 0;
        sscanf(argv[i], "%o", &buffer);
        for (int j = RWX_LENGTH - 1; j >= 0; j--) {
            if (buffer & (1 << j)) {
                printf("%c", rwx[j]);
            } else {
                printf("-");
            }
        }
        printf("\n");
    }

    return 0;
}
