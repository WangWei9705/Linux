/**********************************************************
 * Author        : WangWei
 * Email         : 872408568@qq.com
 * Last modified : 2019-05-11 23:34:34
 * Filename      : cancel.c
 * Description   : 线程的取消
 * *******************************************************/
#include <stdio.h>
#include <pthread.h>

pthread_mutex_t m;
void handler(void* arg) {

    pthread_mutex_unlock(&m);
}

void* routine (void* arg) {
    // 加锁前,将handler压入线程取消处理的栈中，以防中途被取消
    // 线程的取消处理例程的设置
    // pthread_cleanup_push(void(*routine) (void*), void* arg) ;  
    // pthread_cleanup_pop(int execure);
    pthread_cleanup_push(handler, NULL); 
    pthread_mutex_lock(&m);

    printf("[%u] [%s]: abtined the mutex. \n", (unsigned)pthread_self(), __FUNCTION__);
    sleep(10);            // 睡眠期间若线程被取消，则handler函数将被执行

    // 解锁后，将handler从栈中弹出
    pthread_mutex_unlock(&m);
    pthread_cleanup_pop(0);

    pthread_exit(NULL);

}

int main()
{
    pthread_mutex_init(&m, NULL);       // 互斥锁的初始化

    pthread_t tid;
    pthread_create(&tid, NULL, routine, NULL);

    // 睡眠1s后，向子线程（指定线程）发送一个取消请求
    sleep(1);
    pthread_cancel(tid);

    // 此时子线程虽然被取消了，但handler自动是否，因此主线程可加锁
    pthread_mutex_lock(&m);    // 加锁
    printf("[%u] [%s]: abtained the mutex. \n ",(unsigned)pthread_self(), __FUNCTION__);
    pthread_mutex_unlock(&m);        // 解锁
    return 0;
}

