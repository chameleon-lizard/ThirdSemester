#include <sys/types.h>
#include <string.h>
#include <signal.h>
#include <unistd.h>
#include <stdio.h>

enum
{
    DECREASE = 4,
    INCREASE = 5
};

void
fsig(int sig)
{
    int towrite;
    if (sig == SIGUSR1) {
        towrite = 0;
    } else {
        towrite = 1;
    }
}

void
fprint(int sig) 
{

}

int
main(int argc, char *argv[])
{
    struct sigaction action;
    memset(&action, 0, sizeof(action));
    action.sa_handler = fsig;

    sigset_t set1;
    sigset_t set2;

    sigemptyset(&set1);
    sigaddset(&set1, SIGUSR1);
    sigaddset(&set1, SIGUSR2);
    sigprocmask(SIG_BLOCK, &set1, &set2);

    sigaction(SIGUSR1, &action, NULL);
    sigaction(SIGUSR2, &action, NULL);

    printf("%d\n", getpid());
    fflush(stdout);

    while (1) {
        sigsuspend(&set2);
        printf("%d %d\n",
                flag == 1 ? SIGUSR1 : SIGUSR2,
                flag == 1 ? (sum += INCREASE) : (sum -= DECREASE)
                );
        fflush(stdout);

        if (sum < 0) {
            _exit(0);
        }
    }

    return 0;
}
