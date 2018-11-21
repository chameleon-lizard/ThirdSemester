#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>

unsigned long long hash_function(unsigned long long);

enum
{
    ARG_AMOUNT = 4,
    COUNT_ARG = 3,
    DEC_BASE = 10,
    HEX_BASE = 16,
    RWX = 0660,
    H_ARG = 2
};

int
main(int argc, char* argv[])
{
    int file = 0;
    if (argc < ARG_AMOUNT || (file = open(argv[1], O_WRONLY | O_CREAT, RWX)) < 0) {
        return 1;
    }

    unsigned long long h = strtoll(argv[H_ARG], NULL, HEX_BASE);
    unsigned long long count = strtoll(argv[COUNT_ARG], NULL, DEC_BASE);
    long number_size = sizeof(h);

    if (count == 0) {
        close(file);
        return 0;
    }

    if (lseek(file, (long) (count - 1) * number_size, SEEK_END) < 0  
            || write(file, &h, number_size) != number_size) {
        close(file);
        return 1;
    }

    for (unsigned long long i = 1; i < count; i++) {
        h = hash_function(h);

        if (lseek(file, (long) -2 * number_size, SEEK_CUR) < 0
                || write(file, &h, number_size) != number_size) {
            close(file);
            return 1;
        }
    }

    close(file);

    return 0;
}
