/**********************************************************
 * Author        : WangWei
 * Email         : 872408568@qq.com
 * Last modified : 2019-05-06 22:00:56
 * Filename      : signal.c
 * Description   : 信号相关 
 * *******************************************************/

#include <stdio.h>
#include <signal.h>
#include <stdlib.h>

#include <sys/types.h>
#include <unistd.h>

void f(int sig) {
    printf("捕捉到一个信号：%d \n",sig);
}

int main()
{
    //   sighandler_t signal(int signum, sighandler_t handler);
    //
    signal(SIGHUP,SIG_IGN);   // 设置SIGHUP响应动作：忽略
    signal(SIGINT,SIG_DFL);   // 设置SIGINT响应动作：默认
    signal(SIGQUIT,f);        // 设置SIGQUIT响应动作：执行函数f()


    printf("[%d]: 我正在等待信号...\n",getpid());
    pause();  // 暂停进程等待信号到来

    return 0;
}

