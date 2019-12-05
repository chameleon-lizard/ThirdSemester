#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int
main(int argc, char *argv[])
{
    if (argc < 3) {
        return 1;
    }

    int fd[2];
    pipe(fd);
    int pids[2] = { 0 };
    FILE *files[2] = { 0 };

    if (!(pids[0] = fork())) {
        close(fd[0]);
        if ((files[0] = fopen(argv[1], "r")) == 0) {
            return 1;
        }
        int sum1 = 0;
        int currentNumber1 = 0;
        while (fscanf(files[0], "%d", &currentNumber1) != EOF) {
            sum1 += currentNumber1;
        }
        write (fd[1], &sum1, sizeof(sum1));
        close(fd[1]);
        fclose(files[0]);
        _exit(0);
    } else {
        if (!(pids[1] = fork())) {
            close(fd[0]);
            if ((files[1] = fopen(argv[2], "r")) == 0) {
                return 1;   
            }
            int sum2 = 0;
            int currentNumber2 = 0;
            while (fscanf(files[1], "%d", &currentNumber2) != EOF) {
                sum2 += currentNumber2;
            }
            write (fd[1], &sum2, sizeof(sum2));
            close(fd[1]);
            fclose(files[1]);
            _exit(0);
        } else {
            int status[2] = { 0 };
            close(fd[1]);

            waitpid(pids[1], &status[1], 0);
            int sum3 = 0;
            int sum4 = 0;
            read(fd[0], &sum3, sizeof(sum3));
            waitpid(pids[0], &status[0], 0);
            read(fd[0], &sum4, sizeof(sum4));
            close(fd[0]);

            printf("%d\n", sum4);
            fflush(stdout);
            printf("%d\n", sum3);
            fflush(stdout);
            printf("%d\n", sum3 + sum4);
            fflush(stdout);
            _exit(0);
        }
    }
}
