#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

enum
{
    FIRST_YEAR = 1900,
    ARG_COUNT = 3,
    ARG_YEAR = 1,
    ARG_DAY = 2
};

int
main(int argc, char* argv[])
{
    if (argc < ARG_COUNT) {
        return 1;
    }

    int year = atoi(argv[ARG_YEAR]) - FIRST_YEAR;
    int day = atoi(argv[ARG_DAY]);

    struct tm current_time = {0};
    current_time.tm_isdst = -1;
    current_time.tm_year = year;
    current_time.tm_mday = day;
    mktime(&current_time);
    current_time.tm_year += FIRST_YEAR;
    current_time.tm_mon += 1;

    if (current_time.tm_wday == 0) {
        current_time.tm_wday = 7;
    }

    printf("%d %d %d ", current_time.tm_year, current_time.tm_mon, current_time.tm_mday);
    printf("%d\n", current_time.tm_wday);

    return 0;
}
