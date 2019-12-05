#include <sys/sem.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <wait.h>

int *pids;
int n;
int seed;
int semid;

int 
gen_time(void)
{
    srand(seed);
    return (rand() % 9 + 1) * 1E5;
}

void
hndlr(int sig)
{
    for (int i = 0; i < n; i++) {
        kill(pids[i], SIGKILL);
    }

    while(wait(NULL) != -1);
}

void
philosopher(int id)
{
    struct sembuf p1 = { id, 1, SEM_UNDO };
    struct sembuf p2 = { (id + 1) % n, 1, SEM_UNDO };
    struct sembuf v1 = { id, 1, SEM_UNDO };
    struct sembuf v2 = { (id + 1) % n, 1, SEM_UNDO };
    struct sembuf p[2] = { p1, p2 };
    struct sembuf v[2] = { v1, v2 };

    semop(semid, v1, 1);
    while (1) {
        usleep(gen_time());
        semop(semid, p, 2);
        usleep(gen_time());
        semop(semid, v, 2);
    }
}

int
main(int argc, char *argv[])
{
    if (argc < 3) {
        return 1;
    }

    sscanf(argv[3], "%d", &seed);
    int key;
    sscanf(argv[1], "%d", &key);
    sscanf(argv[2], "%d", &n);

    semid = semget(key, n, IPC_CREAT | 0666);
    pids = (int *) calloc(n, sizeof(*pids));

    for (int i = 0; i < n; i++) {
        if (!(pids[i] = fork())) {
            philosopher(i);
        }
    }

    return 0;
}
