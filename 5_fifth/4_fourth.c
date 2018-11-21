#include <sys/stat.h>

enum
{
    GID_OFF = 3,
    UID_OFF = 6
};

struct Task
{
    unsigned uid;
    int gid_count;
    unsigned *gids;
};

int
isGid(unsigned stat_gid, unsigned* task_gid, int amount)
{
    for (int i = 0; i < amount; i++) {
        if (stat_gid == task_gid[i]) {
            return 1;
        }
    }
    
    return 0;
}

int
myaccess(const struct stat *stb, const struct Task *task, int access)
{
    if (!task->uid) {
        return 1;
    }

    if(!task->gid_count) {
        return 0;
    }

    if (stb->st_uid == task->uid) {
        return  (access << UID_OFF & stb->st_mode) == (unsigned int) access << UID_OFF;
    }

    if (isGid(stb->st_gid, task->gids, task->gid_count)) {
        return (access << GID_OFF & stb->st_mode) == (unsigned int) access << GID_OFF;
    }

    return (access & stb->st_mode) == (unsigned int) access;
}
