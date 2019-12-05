#include <stdio.h>

int
main(void)
{
    int a = 0;
    int b = 0;
    while (scanf("%d", &a) != EOF) {
        while (a) {
            b += a & 1;
            a >>= 1;
        }

        printf("%d\n", b & 1);
        b = 0;
    }

    return 0;
}
