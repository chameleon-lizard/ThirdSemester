#include <malloc.h>
#include <stdlib.h>
#include <stdio.h>

enum
{
    UPPER_BOUND = 100
};

int
main(void)
{
    int n = 0;

    scanf("%d", &n);

    int *values = malloc(n * sizeof(long));
    int *probabilities = malloc(n * sizeof(long));


    for (int i = 0; i < n; i++) {
        scanf("%d %d", &values[i], &probabilities[i]);
    }

    int m = 0;
    int seed = 0;
    scanf("%d %d", &m, &seed);
    srand(seed);

    for (int i = 0; i < m; i++) {
        int random_number = (int) (rand() / (RAND_MAX + 1.0) * UPPER_BOUND);

        int prob_sum = 0;
        for (int j = 0; j < n; j++) {
            prob_sum += probabilities[j];
            if (random_number < prob_sum) {
                printf("%d ", values[j]);
                break;
            }
        }
    }

    free(values);
    free(probabilities);
    printf("\n");
}
