#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int
main(void)
{
    int n = 0;
    scanf("%d", &n);

    for (int i = 1; i < n + 1; i++) {
        printf("%d", i);
        fflush(stdout);

        if (i == n) {
            printf("\n");
            fflush(stdout);
        } else if (i != 0) {
            printf(" ");
            fflush(stdout);
        }

        if (fork()) {
            wait(NULL);
            exit(0);
        }
    }

    return 0;
}
