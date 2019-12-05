#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>
#include <time.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/file.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <sys/wait.h>
#include <signal.h>
#include <limits.h>

int
main(int argc, char *argv[])
{
    int cmdStart = 2;
    for (int i = 2; i < argc; i++) {
        if (strcmp(argv[i], argv[1]) == 0) {
            long long size = 0;
            for (int j = 0; j < i - cmdStart; j++) {
                size += sizeof(argv[j]);
            }

            char *cmd = calloc(size + i - cmdStart, sizeof(*cmd));
            size = 0;
            for (int j = 2; j < i - cmdStart; j++) {
                for (unsigned long k = 0; k < strlen(argv[j]); k++) {
                    cmd[size] = argv[j][k];
                    size++;
                }
            }

            if (!fork()) {
                execlp("/bin/sh", "sh",  "-c", cmd, NULL);
            } else {
                free(cmd);
                cmdStart = i;
            }
        }
    }

    return 0;
}
