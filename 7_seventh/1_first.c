#include <stdlib.h>
#include <stdio.h>
#include <time.h>

int
main(int argc, char *argv[])
{
    if (argc < 5) {
        return 1;
    }
    
    unsigned int count = atoi(argv[1]);
    int low = atoi(argv[2]);
    int high = atoi(argv[3]);
    unsigned int seed = atoi(argv[4]);

    srand(seed);

    for (unsigned int i = 0; i < count; i++) {
        printf("%d\n", (int) (rand() / (RAND_MAX + 1.0) * (high - low)) + low);
    }
    
    return 0;
}
