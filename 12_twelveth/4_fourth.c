#include <sys/stat.h>
#include <stdlib.h>
#include <unistd.h>
#include <limits.h>
#include <fcntl.h>
#include <stdio.h>
#include <wait.h>


enum
{
    PROG_LENGTH = 1000
};

int
main(int argc, char *argv[])
{
    unsigned mod = atoi(argv[2]);
    creat(argv[1], 0751);

    char *tempfile = { 0 };
    char tmpdir[PATH_MAX] = "/tmp";
    if ((tempfile = getenv("XDG_RUNTIME_DIR")) == NULL) {
        if ((tempfile = getenv("TMPDIR")) == NULL) {
            tempfile = tmpdir;
        }
    }

    char sourcefile[PATH_MAX];
    snprintf(sourcefile, PATH_MAX, "%s/%d.c", tempfile, getpid());

    FILE *file = 0;
    if (argc < 2 || !(file = fopen(sourcefile, "w+"))) {
        return 1;
    }

    fprintf(file, 
            "#include <stdio.h>\nint\nmain(void)\n{\nunsigned n;\nscanf(\"%%u\",&n);\n"
            "printf(\"%%u\\n\",(n*(n+1)/2)%% %u);\nreturn 0;\n}",
            mod);
    fclose(file);

    if (!fork()) {
        execlp("gcc", "gcc", sourcefile, "-o", argv[1], NULL);
        _exit(1);
    }

    wait(NULL);

    chmod(argv[1], 0751);

    return 0;
}
