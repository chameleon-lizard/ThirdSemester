#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int
exec_func(char *cmd) 
{
    if (!fork()) {
        execlp(cmd, cmd, NULL);
        _exit(1);
    } else {
        int status = 0;
        wait(&status);

        return WIFEXITED(status) && !WEXITSTATUS(status);
    }
}

int
main(int argc, char *argv[])
{
    if (argc < 4) {
        return 1;
    }

    return !((exec_func(argv[1]) || exec_func(argv[2])) && exec_func(argv[3]));
}
