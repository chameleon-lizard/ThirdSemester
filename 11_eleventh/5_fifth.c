#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

enum
{
    SIGNAL_AMOUNT = 3
};

volatile int sigcount = 0;
volatile int lastPrime = 0;

int 
is_prime(int number)
{
    if (number < 2) {
        return 0;
    }

    for (volatile int i = 2; i * i < number; ++i) {
        if (number % i == 0) {
            return 0;
        }
    }
    return 1;
}

void
int_signal(int sig)
{
    if (sigcount != SIGNAL_AMOUNT) {
        printf("%d\n", lastPrime);
        fflush(stdout);
        sigcount++;
        signal(SIGINT, int_signal);
    } else {
        exit(0);
    }
}

void
term_signal(int sig)
{
    exit(0);
}

int
main(void)
{
    printf("%d\n", getpid());
    fflush(stdout);

    signal(SIGINT, int_signal);
    signal(SIGTERM, term_signal);

    volatile int low = -1;
    volatile int high = -1;
    scanf("%d %d", &low, &high);

    for (volatile int i = low; i < high; i++) {
        if (is_prime(i)) {
            lastPrime = i;
        }
    }

    printf("-1\n");
    fflush(stdout);

    return 0;
}
