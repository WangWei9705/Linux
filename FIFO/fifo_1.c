/**********************************************************
 * Author        : WangWei
 * Email         : 872408568@qq.com
 * Last modified : 2019-05-05 21:17:56
 * Filename      : fifo_1.c
 * Description   : fifo_1  通过FIFO从键盘接收数据，并发送
 * *******************************************************/
#include "fifo.h"



int main()

{
    //  int access(const char *filenpath, int mode);  
    //   确定文件或文件夹的访问权限。即，检查某个文件的存取方式，比如说是只读方式、只写方式等.
    //   如果指定的存取方式有效，则函数返回0，否则函数返回-1。

    if(access(FIFO,F_OK)) {

        mkfifo(FIFO, 0644);
    }

    int fifo = open(FIFO, O_WRONLY);

    char buf[20];
    bzero(buf, 20);

    fgets(buf, 20, stdin);
    int n = write(fifo, buf, strlen(buf));   // 将数据写入FIFO

    printf("已发送:%d 字节\n",n);
    return 0;
}

