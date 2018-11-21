#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int
main(void)
{
    int pid = fork();
    if (pid != 0) {
        wait(NULL);
        printf(" 1\n");
    } else {
        pid = fork();
        if (pid != 0) {
            wait(NULL);
            printf(" 2");
        } else {
            printf("3");
        }
    }
}
