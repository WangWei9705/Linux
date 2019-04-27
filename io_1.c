#include <unistd.h>
#include <stdio.h>
#include <sys/stat.h>   // open函数头文件
#include <sys/types.h>
#include <fcntl.h>

// 文件IO的open 与close 的使用
// open函数用来打开一个指定的文件并获得文件描述符，或者创建一个新文件  
// int open(const char *pathname, int flags);
// int open(const char *pathname, int flags, mode_t mode)
//
//close函数关闭文件并释放相应资源
// int close (int fd);

int main()
{
    // 打开文件1.txt 不存在则创建
    int fd = open("1.txt",O_CREAT | O_TRUNC | O_WRONLY, 0644);
    printf("fd: %d \n",fd);
    
    close(fd);      // 文件使用完毕后必须关闭，这点与malloc 函数相似
    return 0;
}

