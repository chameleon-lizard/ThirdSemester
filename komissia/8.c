#include <stdlib.h>
#include <stdio.h>

int
main(int argc, char *argv[])
{
    if (argc < 5) {
        return 1;
    }

    int count = atoi(argv[1]);
    int low = atoi(argv[1]);
    int high = atoi(argv[1]);
    int seed = atoi(argv[1]);

    srand(seed);

    for (int i = 0; i < count; i++) {
        printf("%d", (int) (rand() / (RAND_MAX + 1.0) * (high - low)) + low);
    }

    return 0;
}
