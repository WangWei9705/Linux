/**********************************************************
 * Author        : WangWei
 * Email         : 872408568@qq.com
 * Last modified : 2019-05-18 22:33:57
 * Filename      : pro_con.cpp
 * Description   : 生产者消费者模型的实现(使用条件变量)
 * *******************************************************/
#include <pthread.h>
#include <queue>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <iostream>
using namespace std;
#define Max 10

class BlockQueue {


private:
    std::queue<int> _queue;
    size_t _capacity;
   // 线程安全实现成员
    pthread_mutex_t lock;
    pthread_cond_t _pro;    // 生产者
    pthread_cond_t _con;    // 消费者
    

private:
    void QueueLock() {
        pthread_mutex_lock(&lock);
    }

    void QueueUnlock() {
        pthread_mutex_unlock(&lock);
    }

    void ProductorWait() {
        pthread_cond_wait(&_pro, &lock);
    }

    void ProductorWakeup() {
        pthread_cond_signal(&_pro);
    }
    void ConsumerWait() {
        pthread_cond_wait(&_con, &lock);
        
    }

    void ConsumerWakeup() {
        pthread_cond_signal(&_con);
    }
    bool IsEmpty() {
        return _queue.empty();
    }
    bool IsFull() {
        if(_queue.size() == _capacity) {
            return true;
        }
        return false;
    }
// 封装入队出队
public:
    BlockQueue(size_t capacity = Max):_capacity(capacity) {
        pthread_mutex_init(&lock, NULL);
        pthread_cond_init(&_pro, NULL);
        pthread_cond_init(&_con, NULL);

    }

    void QueuePush(const int& data) {
        QueueLock();

        while(IsFull()) {
            ProductorWait();
        }

        QueuePush(data);
        ConsumerWakeup();
     
        QueueUnlock();
    }

    void QueuePop(int& data) {
        QueueLock();

        while(IsEmpty()) {
            ConsumerWait();
        }

        data = _queue.front();
        _queue.pop();

        ProductorWakeup();
        QueueUnlock();
    }

    ~BlockQueue() {

        pthread_mutex_destroy(&lock);
        pthread_cond_destroy(&_pro);
        pthread_cond_destroy(&_con);
    }



};


void* productor(void* args) {
    BlockQueue* q = (BlockQueue*)args;

    srand((unsigned long)time(NULL));
    while(1) {
        int data = rand() % 1024;
        q->QueuePush(data);

        cout << "productor put done:" << data << endl;
        sleep(1);


    }
}


void* consumer(void* args) {
    BlockQueue* q = (BlockQueue*) args;
    int data;

    while(1) {
        q->QueuePop(data);
        cout <<" consumer get data:"<< data << endl;
        
    }

}

int main()
{
    BlockQueue q;

    pthread_t ctid,ptid;

    pthread_create(&ctid, NULL, consumer, (void*)&q);
    pthread_create(&ptid, NULL, productor, (void*)&q);

    pthread_join(ctid, NULL);
    pthread_join(ptid, NULL);

#if 0

    for(i = 0; i < 4; i++) {
        ret = pthread_create(&ptid[i], NULL, productor, (void*)q);
        if(ret != 0) {
            cout << "pthread :" << pthread_self() <<"create errno" << endl;
            return -1;
        }
    }

    for (i = 0; i < 4; i++) {
        ret = pthread_create(&ctid[i], NULL, consumer, (void*)q);
        if(ret != 0) {
            cout << "pthread:"<< pthread_self() << "create errno" << endl;
            return -1;
        }
    }

    for(i = 0; i < 4; i++) {
        pthread_join(ptid[i], NULL);
    }

    for(i = 0; i < 4; i++) {
        pthread_join(&ctid[i], NULL);
    }

#endif
    return 0;
}

