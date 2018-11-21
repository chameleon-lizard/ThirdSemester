#include <sys/wait.h>
#include <unistd.h>

int
mysys(const char *str)
{
    int pid = 0;
    if ((pid = fork()) == 0) {
        execl("/bin/sh", "sh", "-c", str, NULL);
        _exit(127);
    } 
    
    if (pid == -1){
        return -1;
    } else {
        int status = 0;
        waitpid(pid, &status, 0);
        
        if (WIFSIGNALED(status)) {
            return WTERMSIG(status) + 128;
        } 

        if (WIFEXITED(status)) {
            return WEXITSTATUS(status);
        }
    }

    return 0;
}
