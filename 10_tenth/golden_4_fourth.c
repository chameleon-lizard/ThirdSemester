#include <sys/wait.h>
#include <malloc.h>
#include <unistd.h>
#include <string.h>

int
main(int argc, char *argv[])
{
    if (argc == 1) {
        return 1;
    }

    long long stringLength = 0;
    for (int i = 1; i < argc; i++) {
        stringLength += strlen(argv[i]);
    }

    char *string = calloc(stringLength + 3 * (argc - 1) + 1, sizeof(string));
    long long stringPos = 0;

    for (int i = 1; i < argc; i++) {
        stringLength = strlen(argv[i]);
        for (int j = 0; j < stringLength; j++) {
            string[stringPos] = argv[i][j];
            stringPos++;
        }

        if ((i + 1) != argc) {
            string[stringPos] = ' ';
            string[stringPos + 1] = '|';
            string[stringPos + 2] = ' ';
            stringPos += 3;
        }
    }

    string[stringPos++] = 0;

    if (!fork()) {
        execlp("/bin/sh", "sh", "-c", string, NULL);
        _exit(1);
    } else {
        int status;
        wait(&status);
        if (WIFEXITED(status)) {
            free(string);
            return WEXITSTATUS(status);
        }
    }
}
