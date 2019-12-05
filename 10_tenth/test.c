#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>

#include <sys/types.h>
#include <fcntl.h>
#include <signal.h>
void body(FILE * wr, FILE * rd, int pr, int temp, int n){
     printf("%d\n", fscanf(rd, "%d", &temp));
    while(fscanf(rd, "%d", &temp) != EOF && temp < n) {

        if (temp < n) {
            printf("%d %d\n", pr, temp);
            temp++;
            fflush(stdout);
            fprintf(rd, "%d", temp);
        }
    }
    exit(0);
}
int main(int argc, char const *argv[])
{
    if(argc < 2) {
        return 1;
    }
    int fd1[2], fd2[2];
    pipe(fd1);
    pipe(fd2);
    int n;
    if(sscanf(argv[1], "%d", &n) != 1) {
        return 1;
    }
    int pid = fork();

    if (!pid) {
        close(fd1[0]);
        close(fd2[1]);
        int temp = 0;
        FILE *des_w = fdopen(fd1[1], "w");
        FILE *des_r = fdopen(fd2[0], "r");
         body(des_w, des_r, 1, temp, n);
        close(fd2[0]);
        close(fd1[1]);
        return 0;
    }

    pid = fork();
    if (!pid) {
         close(fd2[0]);
        close(fd1[1]);
        int temp = 1;
         FILE *des_w = fdopen(fd2[1], "w");
         FILE *des_r = fdopen(fd1[0], "r");
         fprintf(des_w, "%d", temp);
        int l;
        write(fd2[1], &temp, sizeof(temp));
        read(fd2[0], &l, 4);
        printf("%d\n", l);
         write(fd2[1], &temp, sizeof(temp));
         body(des_w, des_r, 2, temp, n);  
        close(fd1[0]);
        close(fd2[1]);
        return 0;
    }

    close(fd1[0]);
    close(fd1[1]);
    close(fd2[0]);
    close(fd2[1]);
    wait(NULL);
    wait(NULL);
    printf("Done\n");
    return 0;
}
