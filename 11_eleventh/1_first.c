#include <sys/types.h>
#include <signal.h>
#include <unistd.h>
#include <stdio.h>

int sigcount = 0;

void
fsig(int sig)
{
    signal(SIGHUP, fsig);
    
    if (sigcount != 5) {
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
        if (sigcount == 5) {
            break;
        }
    }

    return 0;
}
