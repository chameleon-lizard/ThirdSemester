#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <wait.h>

int
main(int argc, char *argv[])
{
    if (argc < 3) {
        return 1;
    }

    int pipe2[2];
    pipe(pipe2);

    // P1 and P2
    if (!fork()) {
        int pipe1[2];
        pipe(pipe1);
        close(pipe2[0]);

        if (!fork()) {
            dup2(pipe2[1], 1);
            close(pipe2[1]);

            close(pipe1[1]);
            dup2(pipe1[0], 0);
            close(pipe1[0]);

            execlp(argv[3], argv[3], NULL);
            _exit(1);
        }
        
        close(pipe2[1]);

        close(pipe1[0]);
        dup2(pipe1[1], 1);
        close(pipe1[1]);

        int count = atoi(argv[1]);
        int modulo = atoi(argv[2]);

        for (int i = 1; i <= count; i++) {
            printf("%llu ", ((unsigned long long)(i % modulo) * (i % modulo)) % modulo);
            fflush(stdout);
        }

        close(1);
        wait(NULL);
        return 0;
    }

    close(pipe2[1]);

    // P3 and P4
    if (!fork()) {
        if (!fork()) {
            FILE *file = fdopen(pipe2[0], "r");

            int buffer = 0;
            while ((buffer = fgetc(file)) != EOF) {
                if (buffer == ' ') {
                    buffer = '\n';
                }
                putchar(buffer);
            }
            fflush(stdout);
            fclose(file);
            return 0;
        }

        close(pipe2[0]);
        wait(NULL);
        return 0;
    }

    close(pipe2[0]);

    while (wait(NULL) != -1);
    printf("0\n");
    fflush(stdout);

    return 0;
}
