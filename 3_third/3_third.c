#include <unistd.h>
#include <limits.h>
#include <fcntl.h>
#include <stdio.h>

enum
{
    NUMBER_SIZE = sizeof(unsigned),
};

int
main(int argc, char *argv[])
{
    int file = 0;
    if (argc == 0 || (file = open(argv[1], O_WRONLY | O_TRUNC | O_CREAT, 0600)) == -1) {
        return 1;
    }

    unsigned current_number = 0;
    while (scanf("%u", &current_number) == 1) {
        char buffer[NUMBER_SIZE] = { 0 };
        for (int i = 0; i < NUMBER_SIZE; i++, current_number >>= CHAR_BIT) {
            buffer[NUMBER_SIZE - i - 1] = current_number;
        }

        if (write(file, &buffer, NUMBER_SIZE) != NUMBER_SIZE) {
            close(file);
            return 1;
        }
    }

    close(file);
    return 0;
}
