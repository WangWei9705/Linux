#include "comm.h"
#include <signal.h>

int shmid;

void rmid(int sig) {

    // 信号来了就删除SHM
    shmctl(shmid, IPC_RMID, NULL);   // shmctl 获取/设置共享内存相关属性

}


int main()
{
    signal(SIGINT, rmid);

    key_t key = ftok(PATHNAME, PROJ_ID);
    shmid = shmget(key, SHMSZ, IPC_CREAT|0666);

    char *p = shmat(shmid, NULL, 0);
    bzero(p, SHMSZ);

    pid_t pid = getpid();    // server将自身PID放入shm的钱4个字节中
    memcpy(p, &pid, sizeof(pid_t));

    fgets(p + sizeof(pid_t), SHMSZ, stdin);   // 从键盘将数据填入SHM中
    pause();      // 等待client的信号去删除shm

    return 0;
}

