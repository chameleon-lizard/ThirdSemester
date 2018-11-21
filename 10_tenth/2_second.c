#include <unistd.h>
#include <stdio.h>
#include <wait.h>

enum
{
    TOREAD = sizeof(int)
};

int
main(void)
{
    int fd[2] = { 0 };

    if (pipe(fd) == -1) {
        return 1;
    }

    int number = 0;
    while (scanf("%d", &number) == 1) {
        write(fd[1], stdin, TOREAD);
    }

    int sum = 0;
    if (!fork()) {
        if (!fork()) {
            close(fd[1]);

            int current_number = 0;
            while (read(fd[0], &current_number, sizeof(current_number))) {
                sum += current_number;
            }

            printf("%d\n", sum);
            fflush(stdout);
            _exit(0);
        }
        wait(NULL);
        _exit(0);
    }
    wait(NULL);

    return 0;
}
