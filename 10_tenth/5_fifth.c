#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <wait.h>

int
main(int argc, char *argv[])
{
    if (argc < 2) {
        return 1;
    }

    int pipe1[2];
    int pipe2[2];
    pipe(pipe1);
    pipe(pipe2);

    FILE *init_input = fdopen(pipe1[1], "w");
    fprintf(init_input, "1\n");
    fflush(init_input);

    int maxNumber = atoi(argv[1]);

    if (!fork()) {
        close(pipe1[1]);
        close(pipe2[0]);

        int number = 0;
        FILE *output = fdopen(pipe2[1], "w");
        FILE *input = fdopen(pipe1[0], "r");
        fflush(input);
        while (fscanf(input, "%d", &number) == 1 && number != maxNumber) {
            printf("1 %d\n", number++);
            fflush(stdout);
            if (number >= maxNumber) {
                _exit(0);
            }
            fprintf(output, "%d\n", number);
            fflush(output);
        }
        fclose(output);
        fclose(input);
        _exit(0);
    } else {
        close(pipe2[1]);
        close(pipe1[0]);
        if (!fork()) {
            int number = 0;
            FILE *output = fdopen(pipe1[1], "w");
            FILE *input = fdopen(pipe2[0], "r");
            fflush(input);
            while (fscanf(input, "%d", &number) == 1 && number != maxNumber) {
                printf("2 %d\n", number++);
                fflush(stdout);
                if (number >= maxNumber) {
                    _exit(0);       
                }   
                fprintf(output, "%d\n", number);
                fflush(output);
            }
            fclose(output);
            fclose(input);
            _exit(0);
        }
        close(pipe1[1]);
        close(pipe2[0]);
        while (wait(NULL) != -1);
        printf("Done\n");
        fflush(stdout);
        fclose(init_input);
        return 0;
    }

    return 0;
}
