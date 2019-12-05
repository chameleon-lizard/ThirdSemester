#include <stdio.h>
#include <math.h>

enum
{
    ROUND_VALUE = 10000,
    PERCENTAGE = 100
};

int
main(int argc, char *argv[])
{
    if (argc < 3) {
        return 1;
    }

    double initial_value = 0;
    sscanf(argv[1], "%lf", &initial_value);

    for (int i = 2; i < argc; i++) {
        double change = 0;
        sscanf(argv[i], "%lf", &change);

        initial_value = round(initial_value * ROUND_VALUE * (PERCENTAGE + round(change * ROUND_VALUE) / ROUND_VALUE) / PERCENTAGE) / ROUND_VALUE;
    }

    printf("%.4lf\n", initial_value);

    return 0;
}
