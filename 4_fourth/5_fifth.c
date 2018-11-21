#include <stdio.h>
#include <fcntl.h>

int
main(int argc, char* argv[])
{
    int file = 0;
    if ((file = open(argv[1], O_WRONLY | O_TRUNC | O_CREAT, 0600)) < 0) {
        return 1;
    }

    

    return 0;
}
