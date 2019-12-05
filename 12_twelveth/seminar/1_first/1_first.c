#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <signal.h>
#include <stdio.h>
#include <fcntl.h>

enum
{
    SON_PID = 0,
    GSON_PID = 1
};

int file;
int pid;

void
signalChange(int signal)
{
    char a;

    if(read(file, &a, sizeof(a))) {
        kill(pid, SIGUSR1);
        _exit(0);
    }
    printf("%c\n", a);
    fflush(stdout);
    kill(pid, SIGUSR1);
}

int
main(int argc, char *argv[])
{
    if (argc < 2) {
        return 1;
    }

    int fd[2];
    pipe(fd);

    signal(SIGUSR1, signalChange);

    file = open(argv[1], O_RDONLY);
    int pid1 = 0;

    if (!(pid1 = fork())) {
        close(fd[0]);
        read(fd[1], &pid, sizeof(pid));

        close(fd[1]);
        while(1) {
            pause();
        }
    }

    int pid2 = 0;
    if (!(pid2 = fork())) {
        close(fd[1]);
        int currentPid = getpid();
        write(fd[0], &currentPid, sizeof(pid));

        kill(pid, SIGUSR1);
        while(1) {
            pause();
        }
    }
    close(fd[0]);
    close(fd[1]);

    return 0;
}
