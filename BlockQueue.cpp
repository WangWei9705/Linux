/**********************************************************
 * Author        : WangWei
 * Email         : 872408568@qq.com
 * Last modified : 2019-05-19 14:08:35
 * Filename      : BlockQueue.cpp
 * Description   :C++模拟阻塞队列的生产者消费者模型 
 * *******************************************************/
#include <pthread.h>
#include <queue>
#include <stdlib.h>
#include <iostream>
using namespace std;

#define Num 10 

class BlockQueue {
private:
    std::queue<int> _q;
    size_t _capacity;

    pthread_mutex_t lock;
    pthread_cond_t _pro;
    pthread_cond_t _con;

private:
     void  QueueLock() {
        pthread_mutex_lock(&lock);
    }

     void QueueUnlock() {
         
        pthread_mutex_unlock(&lock);
    }

     void ProWait() {
         pthread_cond_wait(&_pro, &lock);
     }


     void ProWeakup() {
         pthread_cond_signal(&_pro);
     }

     
     void ConWait() {
         pthread_cond_wait(&_con, &lock);
     }
     void ConWeakup() {
         pthread_cond_signal(&_con);
     }

     bool IsFull() {
         if(_q.size() == _capacity) {
             return true;
         }

         return false;
     }

     bool IsEmpty() {
         return _q.empty();
     }

public:
    BlockQueue(size_t capacity = Num) {
        _capacity = capacity;

        pthread_mutex_init(&lock, NULL);
        pthread_cond_init(&_pro, NULL);
        pthread_cond_init(&_con, NULL);

    }

    void QueuePush(const int& data) {
        QueueLock();

        while(IsFull()) {
            // 先唤醒消费者,起来吃面
            ConWeakup();
            cout << "正在吃面..." << endl;
          
            // 生产者休息
            ProWait();
        }

        // 生产者做面
        _q.push(data);

        // 做好面叫醒消费者起来吃面
        ConWeakup();

        QueueUnlock();
    }

    void QueuePop(int& data) {
        QueueLock();

        while(IsEmpty()) {
            // 唤醒生产者，告诉他该起来做面了
            ProWeakup();
            cout << "正在做面..." << endl;

            // 消费者等待生产者做面
            ConWait();
        }

        // 吃面
        data = _q.front();
        _q.pop();

        // 吃完了让生产者继续做面
        ProWeakup();
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

    while(1) {
        int data;
        q->QueuePush(data);
        cout << "面做好了" << endl;
    }
}

void* consumer(void* args) {

    BlockQueue* q = (BlockQueue*)args;

    while(1) {
        int data;    
        q->QueuePop(data);
        cout << "面吃完了" << endl;
        }
}

int main() {

    BlockQueue q;

    pthread_t Ptid,Ctid;

    pthread_create(&Ptid, NULL, productor, (void*)&q);

    pthread_create(&Ctid, NULL, consumer, (void*)&q);
    
    pthread_join(Ptid, NULL);
    pthread_join(Ctid, NULL);
    return 0;
}
