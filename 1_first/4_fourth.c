#include <stdio.h>
#include <ctype.h>

int mystrspccmp(const char *str1, const char *str2)
{
    char is_first_run = 0;

    printf("%d %d\n", *str1, *str2);

    while(*str1 && *str1 == *str2) {
        if(!is_first_run) {
            is_first_run = 1;
        }
        else {
            str1++;
            str2++;
        }
        
        while(isspace(*str1)) {
            str1++;
        }

        while(isspace(*str2)) {
            str2++;
        }
    }
    

    if(*str1 > *str2) {
        return 1;
    }
    else {
        if(*str1 < *str2) {
            return -1;
        }
    }

    while(*str1 != 0 && isspace(*str1)) {
        str1++;
    }

    while(*str1 != 0 && isspace(*str2)) {
        str2++;
    }


    if(*str1 > *str2) {
        return 1;
    }
    else {
        if(*str1 < *str2) {
            return -1;
        }
    }

    return 0;
}

