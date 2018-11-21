#include <stdio.h>
#include <stdlib.h>
#include <math.h>

enum
{
    ROUND_CONST = 10000, 
    PERCENT_TO_FRACTION = 100 
};
// ROUND_CONST:
// Константа, равная 10^n используется для округления, где n - требуемая точность округления.
// 
// PERCENT_TO_FRACTION:
// При делении на эту константу мы получаем дробь из числа процентов.

int
main(int argc, char *argv[])
{
    if (argc == 0) {
        return 1;
    }

    double value = 1;
    double change = 1;

    if (sscanf(argv[1], "%lf", &value)) {
        value = round(value * ROUND_CONST) / ROUND_CONST;
    
        for (int i = 2; i < argc; i++) {
            if (!sscanf(argv[i], "%lf", &change)) {
                return 1;
            }
            else {
                change = round(change * ROUND_CONST) / ROUND_CONST;
                change = (PERCENT_TO_FRACTION + change) / PERCENT_TO_FRACTION;
                value = round(value * change * ROUND_CONST) / ROUND_CONST;
            }
        }

        printf("%.4lf\n", value);

        return 0;
    }

    return 1;
}
