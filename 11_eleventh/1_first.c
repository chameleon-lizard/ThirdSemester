#include <sys/types.h>
#include <signal.h>
#include <unistd.h>
#include <stdio.h>

volatile int sigcount = 0;

enum
{
    SIGNAL_AMOUNT = 5
};

void
fsig(int sig)
{
    signal(SIGHUP, fsig);

    if (sigcount != SIGNAL_AMOUNT) {
        printf("%d\n", sigcount);
        fflush(stdout);
        sigcount++;
    }
}

int
main(void)
{
    signal(SIGHUP, fsig);

    printf("%d\n", getpid());
    fflush(stdout);

    while (1) {
        pause();
        if (sigcount == SIGNAL_AMOUNT) {
            break;
        }
    }

    return 0;
}
