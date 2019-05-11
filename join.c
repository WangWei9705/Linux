/**********************************************************
 * Author        : WangWei
 * Email         : 872408568@qq.com
 * Last modified : 2019-05-11 22:56:11
 * Filename      : join.c
 * Description   : 线程的创建及退出
 * *******************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

void* routine(void* arg) {
    char* s = (char*) arg;
    printf("argument: %s",s);

    sleep(1);
    pthread_exit("Bye~~\n");
}
int main()
{
    pthread_t tid;
    int ret;
    ret = pthread_create(&tid, NULL, routine, NULL);

    // 阻塞等待指定线程退出，并获取其退出值
    void *p;
    pthread_join(tid, &p);

    printf("exit value: %s\n",(char*)p);
    return 0;
}

