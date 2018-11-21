#include <inttypes.h>
#include <stdio.h>

int
main(void)
{
    uint32_t n_oct = 0;
    int w_oct = 0;

    if (scanf("%" SCNo32"%o", &n_oct, &w_oct) != 2) {
        return 1;
    }

    uint32_t max = 1 << n_oct;

    for (uint32_t i = 0, j = 0; i < max; i++) {
        if (i < max/2) { 
            printf("|%*" PRIo32"|%*" PRId32"|%*" PRId32"|\n", w_oct, i, w_oct, i, w_oct, i);
        } else {
            printf("|%*" PRIo32"|%*" PRId32"|%*" PRId32"|\n", w_oct, i, w_oct, i, w_oct, -1 * j);
            j++;
        }
    }
    return 0;
}
