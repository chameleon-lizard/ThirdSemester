#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

enum
{
    LAST_BYTE_ONES = 0xFF,
    BYTE_SIZE = 8,
    OFFSET = 3
};

int
isBigEndian()
{
    unsigned u = 1;
    u <<= OFFSET * BYTE_SIZE;

    return u == 0;
}

unsigned
toBigEndian(unsigned current_number)
{
    unsigned result = 0;
    int mask = LAST_BYTE_ONES;

    int result_size = sizeof(result);
    
    mask &= current_number;
    result |= mask;
    for (int i = 0; i < result_size - 1; i++) {
        result <<= BYTE_SIZE;
        current_number >>= BYTE_SIZE;
        mask = LAST_BYTE_ONES;
        mask &= current_number;
        result |= mask;
    }

    return result;
}

int
main(int argc, char *argv[])
{
    if(argc == 0) {
        return 1;
    }

    int file = open(argv[1], O_WRONLY | O_TRUNC | O_CREAT, 0600);

    if (file == 0) {
        return 1;
    }

    unsigned current_number = 0;
    while (scanf("%u", &current_number) == 1) {
        if (!isBigEndian()) {
            current_number = toBigEndian(current_number);
        }

        write(file, &current_number, sizeof(unsigned));
    }

    close(file);

    return 0;
}
