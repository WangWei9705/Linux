/**********************************************************
 * Author        : WangWei
 * Email         : 872408568@qq.com
 * Last modified : 2019-05-11 23:13:59
 * Filename      : detach.c
 * Description   :线程的分离 
 * *******************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

void* routine(char* arg) {
    pthread_exit(NULL);           // 线程在分离后会自动释放资源
}

int main()
{
    // 初始化一个属性变量，并将分离属性加入该变量
    
    pthread_attr_t attr;
    pthread_attr_init(&attr);
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);

    // 用更高后的属性变量创建一个新线程
    pthread_t tid;
    pthread_create(&tid, &attr, routine, NULL);

    // 主线程暂停，否则return 会导致整个进程退出
    pause();

    return 0;
}

