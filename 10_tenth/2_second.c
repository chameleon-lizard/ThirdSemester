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

    int son_pid;
    int gson_pid;
    if (!(son_pid = fork())) {
        close(fd[1]);
        if (!(gson_pid = fork())) {
            close(fd[1]);

            long long sum = 0;
            int current_number = 0;
            while (read(fd[0], &current_number, sizeof(current_number))) {
                sum += current_number;
            }

            printf("%lld\n", sum);
            fflush(stdout);
            close(fd[0]);
            _exit(0);
        } else {
            close(fd[0]);
            close(fd[1]);
            waitpid(gson_pid, NULL, 0);
            _exit(0);
        }
    } else {
        int number = 0;
        close(fd[0]);
        while (scanf("%d", &number) == 1) {
            write(fd[1], &number, TOREAD);
        }

        close(fd[1]);
        waitpid(son_pid, NULL, 0);
        _exit(0);
    }
}
