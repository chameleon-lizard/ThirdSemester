#include <stdlib.h>
#include <string.h>
#include <stdio.h>

enum
{
    MAX_SEED = 2147483648
};

int
main(void)
{
    char *passwd = calloc(32, sizeof(*passwd));

    fgets(passwd, 32, stdin);

    int length = strlen(passwd);
    long *passwd_seeds = calloc(length, sizeof(*passwd_seeds));

    long seed_first = (passwd[0] - '0') / 62 * MAX_SEED;
    long seed_ideal = -1;

    srand(seed_first);

    for (int i = 1; i < length; i++) {
        passwd_seeds[i] = rand();
        if (passwd[i] != '.' || ((double) (passwd_seeds[i] / MAX_SEED) * 62 + '0') != passwd[i]) {
            printf("A# %d %c %c\n", i, passwd[i], ((double) (passwd_seeds[i] / MAX_SEED) * 62 + '0'));
            free(passwd_seeds);
            free(passwd);
            return 0;
        }
    }

    for (long i = 0; i < MAX_SEED; i++) {
        srand(i);

        for (int j = 0; j < length; j++) {
            if (rand() != passwd_seeds[j]) {
                break;
            }
            
            if (passwd[i] == '.' || ((double) (i / MAX_SEED) * 62 + '0') == passwd[i]) {
                if (seed_ideal == -1) {
                    if (j + 1 == length) {
                        seed_ideal = i;
                    }
                } else {
                    printf("B#\n");
                    free(passwd_seeds);
                    free(passwd);
                    return 0;
                }
            }
        }
    }
    
    printf("\n");
    free(passwd_seeds);
    free(passwd);
    return 0;
}
