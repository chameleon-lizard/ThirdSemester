#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>

int fd[2];
int max;
int pid;

void
f(int sig)
{
    int n;
    read(fd[0], &n, sizeof(n));
    printf("%d %d\n", getpid(), n);
    n++;
    write(fd[1], &n, sizeof(n));

    if(n > max) {
        _exit(1);
    }

    kill(pid, SIGUSR1);

    sig = 0;
}

int
main(int argc, char *argv[])
{
    if (argc < 2) {
        return 1;
    }

    max = strtol(argv[1], NULL, 10);
    signal(SIGUSR1, f);
    pipe(fd);

    sigset_t s1, s2;
    sigemptyset(&s1);
    sigaddset(&s1, SIGUSR1);
    sigprocmask(SIG_BLOCK, &s1, &s2);

    int pid1 = fork();
    if (!pid1) {
        read(fd[0], &pid, sizeof(pid));
        while(1) {
            sigsuspend(&s2);
        }
    }

    int pid2 = fork();
    if (!pid2) {
        int pid = getpid();
        write(fd[1], &pid, sizeof(pid));
        while (1) {
            sigsuspend(&s2);
        }
    }

    int x = 1;
    write(fd[1], &x, sizeof(x));
    kill(pid, SIGUSR1);

    close(fd[0]);
    close(fd[1]);

    return 0;
}
