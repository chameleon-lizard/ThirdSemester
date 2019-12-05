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

    int probabilities[UPPER_BOUND] = { 0 };

    int prob_sum = 0;
    for (int i = 0; i < n; i++) {
        int value = 0;
        int probability = 0;
        scanf("%d %d", &value, &probability);
        for (int i = 0; i < probability; i++) {
            probabilities[prob_sum] = value;
            prob_sum++;
        }
    }

    int m = 0;
    int seed = 0;
    scanf("%d %d", &m, &seed);
    srand(seed);

    for (int i = 0; i < m; i++) {
        int random_number = (int) (rand() / (RAND_MAX + 1.0) * UPPER_BOUND);
        printf("%d\n", probabilities[random_number]);
    }

    printf("\n");
}
