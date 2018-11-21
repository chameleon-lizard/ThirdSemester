#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>

int
main(void)
{
    int currentNumber = 0;
    int pid = 0;
    int parentPid = getpid();
    int status = 0;

    while (scanf("%d", &currentNumber) != EOF) {
        pid = fork();
        if (pid == -1) {
            _exit(1);
        }

        if (pid) {
            wait(&status);
            if (WIFEXITED(status) && (status = WSTOPSIG(status)) == 1) {
                if (getpid() != parentPid) {
                    _exit(1);
                } else {
                    while(wait(NULL) != -1);
                    printf("-1\n");
                    return 0;
                }
            } else {
                printf("%d\n", currentNumber);
                fflush(stdout);
                _exit(0);
            }
        }
    }
}
