#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <wait.h>
#include <time.h>

enum
{
    SON_PID = 0,
    GSON_PID = 1,
    GGSON_PID = 2,
    ERR_VALUE = -1,
    FAMILY_SIZE = 3,
    YEAR_OFFSET = 1900
};

void
print_time(int fd, const char *printfString)
{
    time_t timeNow = 0;
    read(fd, &timeNow, sizeof(timeNow));
    
    struct tm currentTime;
    memset(&currentTime, 0, sizeof(currentTime));
    currentTime.tm_isdst = -1;

    localtime_r(&timeNow, &currentTime);

    switch (printfString[0]) {
    case 'D':
        printf(printfString, currentTime.tm_mday);
        break;
    case 'M':
        printf(printfString, currentTime.tm_mon + 1);
        break;
    case 'Y':
        printf(printfString, currentTime.tm_year + YEAR_OFFSET);
        break;
    default:
        break;
    }

    fflush(stdout);
}

int
main(void)
{
    time_t timeNow = 0;

    int fd[2];
    if (pipe(fd) == ERR_VALUE) {
        return 1;
    }

    int pid[FAMILY_SIZE] = { 0 };
    if (!(pid[SON_PID] = fork())) {
        if (!(pid[GSON_PID] = fork())) {
            if (!(pid[GGSON_PID] = fork())) {
                timeNow = time(NULL);
                
                for (int i = 0; i < FAMILY_SIZE; i++) {
                    write(fd[1], &timeNow, sizeof(timeNow));
                }

                close(fd[1]);
                _exit(0);
            } else {
                waitpid(pid[GGSON_PID], NULL, 0);
                print_time(fd[0], "D:%.2d\n");
                _exit(0);
            }
        } else {
            waitpid(pid[GSON_PID], NULL, 0);
            print_time(fd[0], "M:%.2d\n");
            _exit(0);
        }
    } else {
        waitpid(pid[SON_PID], NULL, 0);
        print_time(fd[0], "Y:%.4d\n");
        _exit(0);
    }
}
