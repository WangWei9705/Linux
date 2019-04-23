// 僵尸进程的实现
// 僵尸进程概念：子进程退出，父进程还在运行，但父进程没有读取到子进程的状态信息，此时子进程进入僵尸状态
//
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main(){
    int pid = fork();
    if(pid < 0) {
        perror("fork perror");
        return 1;
    }
    else if(pid > 0){
        printf("farther[%d] is sleeping ...\n",getpid());
        sleep(10);
    }
    else{
        printf("child[%d] is begin Zombie ...\n",getpid());
        sleep(5);
        exit(0);
    }
    return 0;
}
