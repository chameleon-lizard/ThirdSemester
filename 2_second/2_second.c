#include <stdio.h>

enum
{ 
    MAX_FRACTION = 24, 
};
    
    // MAX_FRACTION:
    // Amount of numbers in the fraction. If the counter is bigger than this number, our value 
    // can't be exactly represented as a float.

int
check_float(unsigned int value)
{
    if (value == 0) {
        return 1;
    }


    while ((value & 1) == 0) {
        value = value >> 1;
    }

    int fraction = 0;

    while (value > 1) {
        value = value >> 1;
        fraction++;
    }

    return fraction < MAX_FRACTION;
}

int
main(void)
{
    unsigned int value = 0;

    while (scanf("%u", &value) == 1) {
        printf("%d\n", check_float(value));
    }

    printf("\n");

    return 0;
}
