#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <limits.h>

int
main(int argc, char *argv[])
{
    if (argc < 2) {
        return 1;
    }

    int file = open(argv[1], O_RDWR);

    if (file == 0) {
        return 1;
    }

    long long current_number = 0;
    long long minimal_number = LLONG_MAX;
    size_t bytesRead = sizeof(current_number);
    int minimal_number_position = 0;
    int n = read(file, &current_number, bytesRead);
    if (n == 0) {
        return 0;
    } else {
        if (current_number < minimal_number) {
            if (current_number == LLONG_MIN) {
                return 0;
            }

            minimal_number = current_number;
            minimal_number_position = 0;
        }
    }

    for (int i = 1; read(file, &current_number, bytesRead) > 0; i++) {
        if(current_number < minimal_number) {
            if (current_number == LLONG_MIN) {
                return 0;
            }
            minimal_number = current_number;
            minimal_number_position = i;
        }
    }

    minimal_number = -minimal_number;
    lseek(file, minimal_number_position * bytesRead, SEEK_SET);
    write(file, &minimal_number, bytesRead);

    close(file);

    return 0;
}
