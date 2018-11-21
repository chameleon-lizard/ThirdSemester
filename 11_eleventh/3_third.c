#include <sys/types.h>
#include <sys/stat.h>
#include <malloc.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>

int
main(int argc, char * argv[])
{
    int N = 0;
    if (argc < 2 || argc < (N = atoi(argv[1]) + 1)) {
        return 1;
    }

    for (int i = 2; i < N; i++) {
        if (!fork()) {
            int file = open(argv[i], O_RDONLY);
            char *executable = calloc();
            execlp();
            _exit(1);
        }
    }

    return 0;
}
