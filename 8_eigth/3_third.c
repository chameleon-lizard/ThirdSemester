#include <sys/wait.h>
#include <stdlib.h>
#include <malloc.h>
#include <unistd.h>
#include <stdio.h>

enum
{
    STRING_AMOUNT = 3,
    STRING_LENGTH = 8
};

int
main(void)
{
    char strings[STRING_AMOUNT][STRING_LENGTH];

    for (int i = 0; i < STRING_AMOUNT; i++) {
        read(0, strings[i], sizeof(strings[i]));
    }

    int pid = 0;
    for (int i = 1; i <= STRING_AMOUNT; i++) {
        if ((pid = fork())) {
            int number = atoi(strings[i - 1]);
            printf("%d %d\n", i, number * number);
            fflush(stdout);
        } else {
            exit(1);
            break;
        }
    }

    while (wait(NULL) != -1);
    return 0;
}
