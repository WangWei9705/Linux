#include "comm.h"

int main(int argc, char **argv) {
    key_t key = ftok(PATHNAME, PROJ_ID);     // 将路径名和项目标识符转换为shm id
    int shmid = shmget(key, SHMSZ, 0666);

    char *p = shmat(shmid, NULL, 0);
    printf("from SHM: %s", p+sizeof(pid_t));

    kill(*((pid_t *) p), SIGINT);
    shmdt(p);

    return 0;
}
