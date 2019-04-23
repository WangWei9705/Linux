#include <stdio.h>                                                                                                     
#include <malloc.h>
#include <assert.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#define NAMEMAX 64
#define PROCMAX 64

typedef enum Status{
    R,                 //就绪
    E                  //结束
}Status;
typedef struct Proc{
    char name[NAMEMAX];//进程名
    char next[NAMEMAX];//下一个需要调度的进程的名字
    size_t run_time;   //要求运行时间
    int prio_num;      //优先数
    Status status;     //状态
}Proc;

typedef struct ProcQueue{//进程队列结构体
    Proc* data;          //指向在堆上动态开辟的内存空间,用来存放进程控制块
    size_t size;         //队列中有效进程的个数
    size_t capatity;     //队列的最大容量,如果数据达到最大容量，就要重新开辟一块更大的内存
}ProcQueue;
//进程队列初始化
void ProcQueueInit(ProcQueue* queue)
{
    if(queue == NULL)
    {
        return;
    }
    queue->size = 0;
    queue->capatity = 100;
    queue->data = (Proc*)malloc(sizeof(Proc)*queue->capatity);
    assert(queue->data != NULL);
}            
//销毁进程队列
void DestroyProcQueue(ProcQueue* queue)
{
    if(queue == NULL)
    {
        return;
    }                                                                                                                                   
    free(queue->data);
    queue->size = 0;
    queue->capatity = 0;
}
void ProcQueuePush(ProcQueue* queue,Proc pro);
//创建进程对象
void CreateProc(ProcQueue* queue, Proc* pro,size_t n)
{
    if(pro == NULL)
    {
        return;
    }
    strcpy(pro->next,pro->name); 
    size_t i = 0;
    printf("请输入进程编号(如P1,P2,P3)...\n");
    for(; i < n; ++i)
    {
        scanf("%s",pro->name);
        pro->status = R;
        srand((unsigned)time(NULL));//采用随机数法为每个进程输入对应数据
        pro->prio_num = rand()%6+1;
        pro->run_time = rand()%6+1;
        ProcQueuePush(queue,*pro);
    }
}
//如果当前进程队列满了，就要动态扩容
Proc* ProcQueueExpand(ProcQueue* queue)
{
    if(queue == NULL)
    {
        return NULL;
    }
    Proc* new_proc = (Proc*)malloc(sizeof(Proc)*2*queue->capatity+1);
    queue->capatity = 2*queue->capatity + 1;
    size_t i = 0;
    for(; i < queue->size ; i++)
    {
        new_proc[i] = queue->data[i];
    }
    free(queue->data);
    return new_proc;
}
//对进程队列进行冒泡排序
void ProcQueueBubble(ProcQueue* queue)
{
    if(queue == NULL)
    {
        return;
    }
    size_t i = 0;
    Proc tmp;
    for(;i < queue->size;i++)
    {
        size_t j = 0;
        for(; j < queue->size-i-1;j++)
        {
            if(queue->data[j].prio_num < queue->data[j+1].prio_num)                                                                     
            {
                tmp = queue->data[j];
                queue->data[j] = queue->data[j+1];
                queue->data[j+1] = tmp;
            }
        }
    }
}
//插入进程
void ProcQueuePush(ProcQueue* queue, Proc pro)
{
    if(queue == NULL)
    {
        return;
    }
    if(queue->size == queue->capatity)
    {
        //进程队列满了，进行动态扩容
        queue->data = ProcQueueExpand(queue);
    }
    //先插入到队列尾部，然后进行排序
    //每次的进程队列都是排好序的
    //如果新插入的进程状态为结束，就不进行排序
    if(pro.status != E)
    {
        queue->data[queue->size++] = pro;
        ProcQueueBubble(queue);
        size_t i = 0;
        for(; i < queue->size;i++)
        {
            if(i+1 == queue->size && queue->data[i+1].status != E)
            {
                strcpy(queue->data[i].next,queue->data[0].name);
            }
            else                                                                                                                        
            {
            strcpy(queue->data[i].next,queue->data[i+1].name);
            }
        }
    }
    else
    {
        strcpy(pro.next,"  ");
        queue->data[queue->size] = pro;
    }
}
//进程调度
void ProcQueueRun(ProcQueue* queue)
{
    if(queue == NULL )
    {
        return;
    }
    if(queue->size != 0)
    {
        if(queue->data[0].run_time > 0)//进程运行时间大于0才能进行调度
        {
            queue->data[0].run_time--;//运行时间减一
            queue->data[0].prio_num--;//优先级数减一
        }
        else
        {
            queue->data[0].status = E;//否则进程状态设置为E
        }
        Proc run_proc = queue->data[0];
        size_t i = 0;
        for(;i < queue->size-1;i++)
        {
            queue->data[i] = queue->data[i+1];
        }                                                                                                                               
        queue->size--;                //进程调度时相当于出队列，所以要从队列中删除
       ProcQueuePush(queue,run_proc); //调度完再入队列
    }
}
//打印进程队列信息
void ProcQueuePrint(ProcQueue* queue,size_t n)
{
    if(queue == NULL)
    {
        return;
    }
    printf("=============================\n");
    printf("NAME STATUS RUNTIME NICE NEXT\n");
    printf("=============================\n");
    size_t i = 0;
    for(; i < n ; i++)
    {
        printf(" %s  ",queue->data[i].name);
        if(queue->data[i].status == R)
        {
            printf("   R   ");
        }else
        {
            printf("   E   ");
        }
        printf("   %lu    ",queue->data[i].run_time);
        printf("  %d  ",queue->data[i].prio_num);
        printf("  %s",queue->data[i].next);
        printf("\n");
    }
}
int main()
{
    ProcQueue queue;
    Proc pro;                                                                                                                           
    size_t n = 0;
    ProcQueueInit(&queue);
    printf("请输入您想拥有的进程数: \n");
    scanf("%lu",&n);
    CreateProc(&queue,&pro,n);
    while(1)
    {
        if(queue.size == 0)
        {
            break;
        }
        printf("\n");
        ProcQueuePrint(&queue,n);
        getchar();
        ProcQueueRun(&queue);
    }
    ProcQueuePrint(&queue,n);
    return 0;
}   
