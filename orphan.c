// 孤儿进程的实现
// 概念：父进程先于子进程退出，此时子进程就会变为孤儿进程，孤儿进程会被init进程领养

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(){
    int pid = fork();
    if(pid < 0) {
        perror("fork error");
        return 1;
    }
    else if(pid == 0) {
        printf("child[%d] \n",getpid());
        sleep(10);
    }
    else {
        printf("farther[%d] \n",getpid());
        sleep(2);
        exit(0);
    }
    return 0;
    
}
