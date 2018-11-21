#include <sys/unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <malloc.h>
#include <dirent.h>
#include <stdio.h>
#include <fcntl.h>
#include <ctype.h>

int
main(int argc, char *argv[])
{
    DIR *directory = 0;

    if (argc < 2 || (directory = opendir(argv[1])) == 0) {
        return 1;
    }

    char *s = calloc(PATH_MAX + 2, sizeof(*s));
    uid_t user_id = getuid();
    struct dirent *dd = 0;
    unsigned long long sum = 0;

    while ((dd = readdir(directory)) != 0) {
        struct stat buf = {};
        snprintf(s, PATH_MAX + 1, "%s/%s", argv[1], dd->d_name);

        if (!strcmp(dd->d_name, ".") || !strcmp(dd->d_name, "..")) {
            continue;
        }
        
        stat(s, &buf);

        if (
                dd->d_name[0] >= 'A' && 
                dd->d_name[0] <= 'Z' &&
                S_ISREG(buf.st_mode) && 
                buf.st_uid == user_id
                ) {
            sum += buf.st_size;
        }
    }

    printf("%llu\n", sum);

    closedir(directory);

    return 0;
}
