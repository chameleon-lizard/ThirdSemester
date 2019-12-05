#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>


int proc(int num) {
    int pid = fork();
    
    if (!pid) {
        char string[8];
        read(0, string, sizeof(string));
        int x;

        x = atoi(string);

        x *= x;

        printf("%d %d\n", num, x);
        fflush(stdout);
    }

    return pid;
}


int main(void) {
    for(int i = 0; i < 3; i++) {
        if (!proc(i + 1)) {
            break;
        }
    }

    while (wait(NULL) != -1);
    return 0;
}
