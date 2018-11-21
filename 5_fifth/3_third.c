#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h>
#include <fcntl.h>
#include <time.h>

enum
{
    FIRST_YEAR = 1900,
    TIME_VALUES = 6,
    ARG_COUNT = 2
};

int
getTime(struct tm *time, FILE *file)
{
    int year = 0;
    int month = 0;
    int day = 0;
    int hour = 0;
    int min = 0;
    int sec = 0;

    if (fscanf(file, "%d/%d/%d %d:%d:%d", &year, &month, &day, &hour, &min, &sec) == TIME_VALUES) {
        time->tm_year = year - FIRST_YEAR; 
        time->tm_mon = month - 1;
        time->tm_mday = day; 
        time->tm_hour = hour; 
        time->tm_min = min; 
        time->tm_sec = sec;
        time->tm_isdst = -1;
        
        return 0;
    } else {
        return 1;
    }
}

int
main(int argc, char* argv[])
{
    FILE *file = 0;
    if (argc < ARG_COUNT || (file = fopen(argv[1], "r+")) == NULL) {
        printf("A");
        return 1;
    }

    struct tm time;
    memset(&time, 0, sizeof(time));
    time_t previous_time = 0;
    time_t current_time = 0;
    
    if (getTime(&time, file) == 0) {
        previous_time = mktime(&time);
        time.tm_year += FIRST_YEAR;

        memset(&time, 0, sizeof(time));
    } else {
        fclose(file);
        return 1;
    }

    while (1) {
        if (getTime(&time, file) == 0) {
            current_time = mktime(&time);
            time.tm_year += FIRST_YEAR;

            printf("%ld\n", current_time - previous_time);
            previous_time = current_time;
            memset(&time, 0, sizeof(time));
        } else {
            break;
        }
    }

    fclose(file);

    return 0;
}
