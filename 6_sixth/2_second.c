#include <string.h>
#include <stdio.h>
#include <time.h>

enum
{
    SECONDS_IN_DAY = 60 * 60 * 24,
    MONTHS_IN_YEAR = 12,
    DAYS_IN_MONTH = 30,
    FIRST_YEAR = 1900,
    SCANF_ARGS = 3,
    YEAR_BDAY = 25,
    MON_BDAY = 9,
    DAY_BDAY = 7
};

int
main(void)
{
    struct tm newCalendar;
    memset(&newCalendar, 0, sizeof(newCalendar));
    newCalendar.tm_isdst = 1;
    newCalendar.tm_mon = MON_BDAY;
    newCalendar.tm_mday = DAY_BDAY;
    newCalendar.tm_year = YEAR_BDAY;
    long long calendar_time = mktime(&newCalendar);

    long long year = 0;
    long long month = 0;
    long long day = 0;

    while (scanf("%lld %lld %lld", &year, &month, &day) == SCANF_ARGS) {
        struct tm current_date;
        memset(&current_date, 0, sizeof(current_date));
        current_date.tm_year = year - FIRST_YEAR;
        current_date.tm_mon = month - 1;
        current_date.tm_mday = day;
        current_date.tm_isdst = -1;
        long long current_time = mktime(&current_date);
        current_time = difftime(current_time, calendar_time);

        year = current_time / SECONDS_IN_DAY / DAYS_IN_MONTH / MONTHS_IN_YEAR;
        current_time %= SECONDS_IN_DAY * DAYS_IN_MONTH * MONTHS_IN_YEAR;

        month = current_time / SECONDS_IN_DAY / DAYS_IN_MONTH;
        current_time %= SECONDS_IN_DAY * DAYS_IN_MONTH;

        day = current_time / SECONDS_IN_DAY;

        printf("%lld %lld %lld\n", year + 1, month + 1, day + 1);
    }

    return 0;
}
