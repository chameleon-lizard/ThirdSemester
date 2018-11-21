#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <malloc.h>
#include <stdlib.h>
#include <limits.h>
#include <stdio.h>
#include <fcntl.h>

int
main(int argc, char *argv[])
{
    if (argc < 2) {
        return 1;
    }

    char *tempfile = {0};
    char tmpdir[PATH_MAX] = "/tmp";
    char scriptfile[PATH_MAX] = {0};
    if ((tempfile = getenv("XDG_RUNTIME_DIR")) == NULL) {
        if ((tempfile = getenv("TMPDIR")) == NULL) {
            tempfile = tmpdir; 
        }
    }

    int pid = getpid();
    snprintf(scriptfile, PATH_MAX, "%s/%d.sh", tempfile, pid);

    FILE *file = 0;
    if ((file = fopen(scriptfile, "w+")) == NULL) {
        return 1;
    }

    fprintf(file, "#! /bin/bash\npython3 -c \"print(1");
    for (int i = 1; i < argc; i++) {
        fprintf(file, "*%s", argv[i]);
    }
    fprintf(file, ")\"\nrm -f $0");

    fclose(file);

    execl("/bin/sh", "sh", scriptfile, NULL);

    return 0;
}
