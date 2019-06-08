/**********************************************************
 * Author        : WangWei
 * Email         : 872408568@qq.com
 * Last modified : 2019-06-08 19:18:07
 * Filename      : ticket.c
 * Description   : 模拟实现抢票程序
 * *******************************************************/
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>

int ticket = 100;
pthread_mutex_t mutex;

// 线程入口函数
void *yellow_bull(void* arg) {
    while(1) {
        // 抢票之前先加锁，保证他同一张票只能被一个人抢
        pthread_mutex_lock(&mutex);
        if(ticket > 0) {
            usleep(1000);
            printf("bull:%d-----get a ticket:%d \n",(int)arg, ticket);
            ticket--;
            // 本次抢票结束，解锁
            pthread_mutex_unlock(&mutex);
        } else {
            printf("Threr is no ticket,exit \n");
            // 加锁之后在线程人一样有可能退出的地方都要解锁
            pthread_mutex_unlock(&mutex);
            pthread_exit(NULL);
        }
    }
    return NULL;
}

int main(int argc, char* argv)
{
    pthread_t tid[4];
    int ret, i;

    // 初始化信号量
    pthread_mutex_init(&mutex, NULL);
    for(i = 0; i < 4; i++) {
        // 创建四个线程
        ret = pthread_create(&tid[i], NULL, yellow_bull, (void*)i);
        // 如果返回值不为0则创建失败
        if(ret != 0) {
            printf("thread create error \n");
            return -1;
        }

    }

    // 进行线程分离
    for(i = 0; i < 4; i++) {
        pthread_join(tid[i], NULL);
    }

    // 销毁互斥锁
    pthread_mutex_destroy(&mutex);
    return 0;
}

