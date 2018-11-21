#include <string.h>


int
parse_rwx_permissions(const char *str)
{
    if (str == NULL) {
        return -1;
    }

    static const char rwx[] = "rwxrwxrwx";

    unsigned int result = 0;
    int i = 0;
    for (i = 0; rwx[i] != 0; i++) {
        if ((str[i] == '-') || (str[i] == rwx[i])) {
            result <<= 1;
            result += (str[i] == rwx[i]);
        } else {
            return -1;
        }
    }

    if (str[i] != 0) {
        return -1;
    }

    return result;
} 
