/**********************************************************
 * Author        : WangWei
 * Email         : 872408568@qq.com
 * Last modified : 2019-05-06 22:30:08
 * Filename      : sig_block.c
 * Description   : 信号阻塞 
 * *******************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

#include <sys/types.h>
#include <sys/wait.h>

void sighandler(int sig) {
    printf("[%d]: catch %d \n",getpid(), sig);
}

int main()
{
    pid_t pid = fork();

    if(pid > 0) {
        signal(SIGINT, sighandler);

        sigset_t sigmask;
        sigemptyset(&sigmask);
        sigaddset(&sigmask,SIGINT);

#ifdef TEST
        printf("[%d]: 进程阻塞... \n",getpid());
        sigprocmask(SIG_BLOCK, &sigmask, NULL);    // 设置阻塞

#endif
        sleep(5);

#ifdef TEST
        printf("[%d]: 解除进程阻塞 \n",getpid);
        sigprocmask(SIG_UNBLOCK, &sigmask, NULL);   // 解除阻塞

#endif
        wait(NULL);    // 让子进程先退出，保证正确显示shell命令
    }

    if(pid == 0) {
        sleep(1);    // 保证父进程做好准备工作
        if(kill(getpid(), SIGINT) == 0) {
            
      // 给附近发送信号SIGINT
      printf("[%d]: 信号已发送 \n", getpid()) ;

    }
    }
    
    return 0;
}

