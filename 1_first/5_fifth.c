#include "stdio.h"
#include "stdlib.h"

struct Data
{
    double first_number;
    int second_number;
    int id;
};

int
comparator(const void *first_value, const void *second_value)
{
    struct Data* first = (struct Data*) first_value;
    struct Data* second = (struct Data*) second_value;

    if(first->first_number == second->first_number) {
        if(first->id < second->id) {
            return -1;
        }
        else {
            return 1;
        }
    } else if (first->first_number - second->first_number > 0) {
        return 1;
    } else if(first->first_number - second->first_number < 0) {
        return -1;
    }

    return 2;
}

int 
main(void)
{
    enum numbers { MAX_PAIRS = 16384 };

    struct Data *values = calloc(MAX_PAIRS, sizeof(*values));
    if (values == 0){
        return 1;
    }

    int i = 0;

    while (i < MAX_PAIRS &&
            scanf("%lf %d", &values[i].first_number, &values[i].second_number) == 2) {
        values[i].id = i;
        i++; 
    }

    qsort(values, i, sizeof(values[0]), comparator);

    for(int j = 0; j < i; j++) {
        printf("\n%.10g %d", values[j].first_number, values[j].second_number);
    }

    printf("\n");

    free(values);

    return 0;
}
