#include <sys/types.h>
#include <sys/sem.h>
#include <sys/ipc.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <wait.h>

int
main(int argc, char *argv[])
{
    if (argc < 2) {
        return 1;
    }

    setvbuf(stdin, NULL, _IONBF, 0);

    int current = 0;
    int key = ftok(argv[0], 'F');
    int count = atoi(argv[1]);
    int semid = semget(key, count, 0600 | IPC_CREAT | IPC_EXCL);

    for (int i = 0; i < count; i++) {
        if (!fork()) {
            while (1) {
                struct sembuf sopsdown[] = 
                { 
                    { (unsigned short) i, -1, SEM_UNDO }
                };

                semop(semid, sopsdown, 1);

                if (scanf("%d", &current) == 1) {
                    printf("%d %d\n", i, current);
                    fflush(stdout);
    
                    int np = (current % count + count) % count;

                    struct sembuf sopsup[] = 
                    { 
                        { (unsigned short) np, 1, SEM_UNDO }
                    };

                    semop(semid, sopsup, 1);
                } else {
                    break;
                }
            }
            semctl(semid, count, IPC_RMID);
        }
    }

    struct sembuf sops[] = 
    { 
        { 0, 1, SEM_UNDO }
    };

    semop(semid, sops, 1);

    while (wait(NULL) != -1);

    return 0;
}
