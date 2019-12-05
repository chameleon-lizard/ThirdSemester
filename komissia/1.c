#include <stdio.h>

int
main(void)
{
    double x, y = 0;

    scanf("%lf %lf", &x, &y);

    if (x > 7 || x < 1 || y > 5 || y < 2 || y > 10 - x) {
        printf("0\n");
    } else {
        printf("1\n");
    }

    return 1;
}
