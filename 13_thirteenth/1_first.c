#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/shm.h>

int main(int argc, char* argv[])
{
    if (argc < 4) {
        return 1;
    }

    int nproc = atoi(argv[1]);
    int key = atoi(argv[2]);
    unsigned long long int max = atoi(argv[3]);

    int semid = semget(key, nproc, IPC_CREAT | 0666);
    struct sembuf semaphores = {0, 1, SEM_UNDO};

    semop(semid, &semaphores, 1);
    int shmid = shmget(key, 2 * sizeof(unsigned int), IPC_CREAT | 0666);
    unsigned long long int *shmaddr = (unsigned long long int*) shmat(shmid, NULL, 0);
    shmaddr[0] = shmaddr[1] = 0;

    for (int i = 0; i < nproc; i++) {
        if (!fork()) {
            struct sembuf pi = {(unsigned short) i, -1, SEM_UNDO};

            while(1) {
                if (semop(semid, &pi, 1) < 0) {
                    return 0;
                }

                printf("%d %llu %llu\n", i + 1, shmaddr[0], shmaddr[1]);
                fflush(stdout);

                if (shmaddr[0] < max) {
                    shmaddr[0]++;
                    int adr = ((unsigned long long) (shmaddr[0] % nproc) * 
                            (shmaddr[0] % nproc) *
                            (shmaddr[0] % nproc) * 
                            (shmaddr[0] % nproc)) % 
                        nproc; 

                    shmaddr[1] = i + 1;

                    struct sembuf v_adr = {(unsigned short) adr, 1, SEM_UNDO};
                    semop(semid, &v_adr, 1);
                } else {
                    return 0;
                }
            }
        }
    }

    wait(NULL);
    semctl(semid, 0, IPC_RMID, 0);
    while (wait(NULL) != -1);

    shmdt(shmaddr);
    shmctl(shmid, IPC_RMID, 0);

    return 0;
}
