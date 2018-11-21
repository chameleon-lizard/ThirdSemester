#include <stdio.h>
#include <stdlib.h>

int
main(int argc, char *argv[]) {
    long long neg_sum = 0;
    long long pos_sum = 0;

    for (int i = 1; i < argc; i++) {
        long long buffer = 0;
        sscanf(argv[i], "%lld", &buffer);
        if (buffer > 0) {
            pos_sum += buffer;
        } else {
            neg_sum += buffer;
        }
    }

    printf("%lld \n%lld\n", pos_sum, neg_sum);

    return 0;
}
