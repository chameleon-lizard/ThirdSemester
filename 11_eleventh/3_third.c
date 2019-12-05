#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <limits.h>
#include <stdio.h>
#include <wait.h>

int
execute_command(char *path)
{
    FILE *file = 0;
    if (!(file = fopen(path, "r"))) {
        return 1;
    }

    char cmd[PATH_MAX] = { 0 };
    fgets(cmd, PATH_MAX, file);
    cmd[strlen(cmd) - 1] = 0;

    if (!fork()) {
        execlp(cmd, cmd, NULL);
        _exit(1);
    }

    return 0;
}

int
main(int argc, char * argv[])
{
    if (argc < 2) {
        return 1;
    }

    int N = atoi(argv[1]) + 1;

    for (int i = 2; i < N && i < argc; i++) {
        if (execute_command(argv[i])) {
            continue;
        }
    }

    int processAmount = 0;
    int status = 0;
    while (wait(&status) != -1) {
        if (WIFEXITED(status) && WEXITSTATUS(status) == 0) {
            processAmount++;
        }
    }

    for (int i = N; i < argc; i++) {
        if (execute_command(argv[i])) {
            continue;
        }

        wait(&status);
        if (WIFEXITED(status) && WEXITSTATUS(status) == 0) {
            processAmount++;
        }
    }

    printf("%d\n", processAmount);

    return 0;
}
