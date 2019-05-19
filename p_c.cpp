#include <iostream>
#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <stdlib.h>

using namespace std;
 
class SynchronizedStack
{
public:
    char ss[100];
    int index;
    pthread_mutex_t mutex;
 
    
SynchronizedStack ()
{
    index = -1;
    for(int i=0;i<100;i++)
        ss[i] = 'a';
    pthread_mutex_init(&mutex,NULL);
}
~SynchronizedStack ()
{
    pthread_mutex_destroy(&mutex);
}
 
void push(char c)
{
 
    if(index<100)
        ss[++index] = c;
    else
        cout << "ss满了！"<< endl;
 
}
char pop()
{
    char s=')';
 
    if(index>=0)
        s = ss[index--];
    else
        cout << "栈空了!" << endl;
 
    return s;
} 
};


void * Consumer(void *arg)
{
    SynchronizedStack  *temp = (SynchronizedStack  *)arg;
    char s;
    for(int i=0;i<30;i++)
    {
        pthread_mutex_lock(&(temp->mutex));
        s = temp->pop();
        if(s!=')')
            cout << "Consumed:" << s << endl;
        pthread_mutex_unlock(&(temp->mutex));
        sleep(1);
    }
}
 
void * Producer(void *arg)
{
    SynchronizedStack  *temp = (SynchronizedStack  *)arg;
 
    for(int i=0;i<26;i++)
    {
        pthread_mutex_lock(&(temp->mutex));
        temp->push((char)(i+65));
        cout << "Produced:" << temp->ss[temp->index] << endl;
        pthread_mutex_unlock(&(temp->mutex));
        sleep(1);
    }
}
int main()
{
    pthread_t pid1,pid2;
    int error1,error2;
    error1 = 0;
    error2 = 0;
    SynchronizedStack * quyu = new SynchronizedStack ();
    error2=pthread_create(&pid2,NULL,Producer,quyu);
    error1=pthread_create(&pid1,NULL,Consumer,quyu);
    if(error1!=0 || error2!=0)
    {
        printf("pthread_cread failed");
        return 0;
    }
    pthread_join(pid1,NULL);
    pthread_join(pid2,NULL);
    return 0;
} 
