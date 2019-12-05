#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <sys/msg.h>

int
main(void)
{
    char s[256];

    key_t id = ftok(filename, 12);

    int semid = semget(id, 2, IPC_CREAT | 0666);
    int mid = semget(id, 256, IPC_CREAT | 0666);

    char *p = shmid();

    return 0;
}
