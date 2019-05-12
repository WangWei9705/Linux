/**********************************************************
 * Author        : WangWei
 * Email         : 872408568@qq.com
 * Last modified : 2019-05-12 17:51:34
 * Filename      : jack.c
 * Description   : 使用信号量写数据
 * *******************************************************/
#include "sem.h"

int main()
{
    // 获取shm、sem对应的按键
    key_t key1 = ftok(PATHNAME, ID4SHM);
    key_t key2 = ftok(PATHNAME, ID4SEM);

    // 获取SHM 的id并映射到本进程的虚拟地址空间中
    int shmid = shmget(key1, SHMSZ, IPC_CREAT|0644);
    char* shmaddr = shmat(shmid, NULL, 0);

    // 获取SEM的id，若新建则初始化它，否则直接获取其id
    int semid = semget(key2, 2, IPC_CREAT|IPC_EXCL|0644);
    if(semid == -1 && errno == EEXIST) {
        semid = semget(key2, 2, 0644);    // 直接获取sem的id
    }
    else {
        seminit(semid, 0, 0);       // 将第0个元素初始化为0，代表数据
        seminit(semid, 1, 1);       // 将死1个元素初始化为1，代表空间
    }

    while(1) {
        sem_p(semid, 1);
        fgets(shmaddr, SHMSZ, stdin);
        sem_v(semid, 0);
    }

    return 0;
}

