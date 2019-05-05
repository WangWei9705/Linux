/**********************************************************
 * Author        : WangWei
 * Email         : 872408568@qq.com
 * Last modified : 2019-05-05 21:34:52
 * Filename      : fifo_2.c
 * Description   :  通过FIFO从fifo_1中接收数据并打印出来
 * *******************************************************/
#include "fifo.h"

int main()
{
    if(access(FIFO, F_OK)) {
        mkfifo(FIFO, 0644);
    }

    int fifo = open(FIFO, O_RDONLY);   // 以制度方式打开管道

    char buf[20];
    bzero(buf, 20);

    read(fifo, buf, 20);

    printf("新消息: %s \n", buf);
    return 0;
}

