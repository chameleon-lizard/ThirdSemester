#include <string.h>
#include <stdio.h>
#include <time.h>

enum
{
    SECONDS_IN_DAY = 60 * 60 * 24,
    FIRST_YEAR = 1900,
    BYEAR = 25,
    BMONTH = 9,
    MONTH = 12,
    DAYS = 30,
    BDAY = 7
};

int
main(void)
{
    long long year = 0;
    long long month = 0;
    long long day = 0;

    struct tm newCal;
    memset(&newCal, 0, sizeof(newCal));
    newCal.tm_isdst = 1;
    newCal.tm_mday = BDAY;
    newCal.tm_mon = BMONTH;
    newCal.tm_year = BYEAR;

    long long calendar_time = mktime(&newCal);

    while (scanf("%lld %lld %lld", &year, &month, &day) == 3) {
        struct tm cal;
        memset(&cal, 0, sizeof(cal));
        cal.tm_year = year - FIRST_YEAR;
        cal.tm_mon = month - 1;
        cal.tm_mday = day;
        cal.tm_isdst = -1;
        long long diff = difftime(mktime(&cal), calendar_time);

        printf("%lld ", diff / SECONDS_IN_DAY / DAYS / MONTH + 1);
        diff %= SECONDS_IN_DAY * DAYS * MONTH;
        printf("%lld ", diff / SECONDS_IN_DAY / DAYS + 1);
        diff %= SECONDS_IN_DAY * DAYS;
        printf("%lld\n", diff / SECONDS_IN_DAY + 1);
    }

    return 0;
}
