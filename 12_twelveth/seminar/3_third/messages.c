#include <sys/msg.h>
#include <sys/ipc.h>
#include <unistd.h>

int
main(void)
{
    int pids[2] = { 0 };

    if (!(pids[0] = fork())) {
        
    } else if (!(pids[1] = fork())) {

    }

    return 0;
}
