#include <sys/stat.h>
#include <malloc.h>
#include <dirent.h>
#include <unistd.h>
#include <stdio.h>

int
main(int argc, char *argv[])
{
    DIR *dir = 0;
    if (argc < 2 || (dir = opendir(argv[1])) == 0) {
        return 1;
    }

    uid_t uid = getuid();

    struct dirent *dd = 0;
    unsigned long long sum = 0;

    char *str = (char *)calloc(PATH_MAX + 3, sizeof(*str));

    while ((dd = readdir(dir)) != 0) {
        struct stat buf = {};
        snprintf(str, PATH_MAX + 2, "%s/%s", argv[1], dd->d_name);

        if (
                dd->d_name[0] >= 'A' && dd->d_name[0] <= 'Z' &&
                S_ISREG(buf.st_mode) &&
                buf.st_uid == uid
                ) {
            sum += buf.st_size;
        }
    }

    printf("%llu\n", sum);

    closedir(dir);

    return 0;
}
