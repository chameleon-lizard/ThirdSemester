#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <sys/msg.h>

// Операция down(s) - вычитает 1, если вычесть нельзя, то процесс блокируется
// и операция считается незавершенной. Является атомарной операцией (Важно, 
// без этого не зачтут определение!).

int
main(void)
{
    key_t ftok(char *fname, char c);
    int semget(key_t, int nsem, int flag);
    int semctl(int semid, int semnum, int cmd, union semum arg);
    // GETVAL - получить значение семафора
    // SETVAL - установить значение семафора
    // GETALL - кинуть в массив значения всех семафоров
    int semop(int semid, struct sembuf *buf, int n);
    void shmdt(void *p);

    return 0;
}
