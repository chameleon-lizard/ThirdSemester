#include <sys/types.h>
#include <signal.h>
#include <unistd.h>
#include <stdio.h>

volatile int mode = 0;

enum
{
    ADD_MODE = 0,
    MULT_MODE = 1
};

void
fsigsum(int sig)
{
    signal(SIGINT, fsigsum);
    mode = ADD_MODE;
}

void
fsigmul(int sig)
{
    signal(SIGQUIT, fsigmul);
    mode = MULT_MODE;
}

int
main(void)
{
    signal(SIGINT, fsigsum);
    signal(SIGQUIT, fsigmul);

    printf("%d\n", getpid());
    fflush(stdout);

    int sum = 0;
    int currentNumber = 0;
    while (scanf("%d", &currentNumber) != EOF) {
        if (!mode) {
            printf("%d\n", sum += (long long) currentNumber);
            fflush(stdout);
        } else {
            printf("%d\n", sum *= (long long) currentNumber);
            fflush(stdout);
        }
    }

    return 0;
}
