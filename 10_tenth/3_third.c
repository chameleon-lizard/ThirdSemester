#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <wait.h>

// (cmd1 < file1 && cmd2) | cmd3 >> file2

int
main(int argc, char *argv[])
{
    if (argc < 6) {
        return 1;
    }

    int fd[2];
    pipe(fd);

    int file1 = 0;
    int file2 = 0;

    if (!fork()) {
        dup2(fd[1], 1);
        close(fd[0]);
        close(fd[1]);
        if (!fork()) {
            if (!(file1 = open(argv[4], O_RDONLY, 0666))) {
                _exit(1);
            } else {
                dup2(file1, 0);
                close(file1);
                execlp(argv[1], argv[1], NULL);
                _exit(1);
            }
        } else {
            int status = 0;
            wait(&status);
            if (WIFEXITED(status) && !WEXITSTATUS(status)) {
                if (!fork()) {
                    execlp(argv[2], argv[2], NULL);
                    _exit(1);
                } else {
                    wait(NULL);
                    _exit(0);
                }
            } else {
                _exit(1);
            }
        }
    } else {
        if (!fork()) {
            dup2(fd[0], 0);
            close(fd[0]);
            close(fd[1]);
    
            if (!(file2 = open(argv[5], O_WRONLY | O_CREAT | O_APPEND, 0666))) {
                _exit(1);
            } else {
                dup2(file2, 1);
                close(file2);
                execlp(argv[3], argv[3], NULL);
                _exit(0);
            }
        } else {
            close(fd[0]);
            close(fd[1]);
    
            while (wait(NULL) != -1);
            return 0;
        }
    }
}
