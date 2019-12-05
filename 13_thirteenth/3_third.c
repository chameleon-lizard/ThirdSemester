#include <sys/ipc.h>
#include <sys/msg.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <wait.h>

struct Message
{
    long type;
    long long x1;
    long long x2;
};

int
main(int argc, char *argv[])
{
    if (argc < 6) {
        return 1;
    }

    int key = atoi(argv[1]);
    int n = atoi(argv[2]);

    struct Message msg;
    msg.x1 = atoll(argv[3]);
    msg.x2 = atoll(argv[4]);
    msg.type = 1;
    long long maxval = atoll(argv[5]);

    int msgid = msgget(key, 0666 | IPC_CREAT);
    int msgsize = sizeof(msg) - sizeof(msg.type);

    for (int i = 0; i <= n; i++) {
        int pid = fork();
        if (!pid) {
            while (1) {
                if (msgrcv(msgid, (void *) &msg, msgsize, i + 1, 0) == -1) {
                    _exit(0);
                }

                long long x3 = msg.x1 + msg.x2;
                printf("%d %lld\n", i, x3);
                fflush(stdout);
                
                if (x3 > maxval || -x3 > maxval) {
                    msgctl(msgid, IPC_RMID, NULL);
                    return 0;
                } else {
                    msg.x1 = msg.x2;
                    msg.x2 = x3;
                    msg.type = x3 % n + 1;
                    msgsnd(msgid, (void *) &msg, msgsize, IPC_NOWAIT);
                }
            }
            _exit(0);
        } else if (pid < 0) {
            msgctl(msgid, IPC_RMID, NULL);
            while (wait(NULL) != -1);
            return 1;
        }
    }

    msgsnd(msgid, (void *) &msg, msgsize, IPC_NOWAIT);

    while (wait(NULL) != -1);

    return 0;
}
