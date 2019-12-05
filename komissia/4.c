#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

int
main(int argc, char *argv[])
{
    if (argc < 3) {
        return 1;
    }

    long long year = atoi(argv[1]) - 1900;
    long long day = atoi(argv[2]);

    struct tm time;
    memset(&time, 0, sizeof(time));
    time.tm_isdst = -1;
    time.tm_year = year;
    time.tm_mday = day;

    mktime(&time);

    time.tm_year += 1900;
    time.tm_mon += 1;

    if (time.tm_wday == 0) {
        time.tm_wday = 7;
    }

    printf("%d %d %d %d\n", time.tm_year, time.tm_mon, time.tm_mday, time.tm_wday);

    return 0;
}
