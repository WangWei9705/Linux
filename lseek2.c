/**********************************************************
 * Author        : WangWei
 * Email         : 872408568@qq.com
 * Last modified : 2019-05-04 15:56
 * Filename      : lseek2.c
 * Description   : lseek 函数的应用——让多个进程在不同的偏移量处
 *                  写入数据
 *
 *       父进程复制文件前半部分，子进程复制文件后半部分
 * *******************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <strings.h>


#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
int main(int argc, char  ** argv)
{
    if(argc != 3) {
        printf("Usage:%s <src> <dst> \n",argv[0]);
        exit(1);
    }

    // 创建一个子进程
    
    pid_t pid = fork();

    // 父子进程都打开源文件和目标文件
    int fd1 = open(argv[1], O_RDONLY);
    int fd2 = open(argv[2], O_CREAT, O_RDWR | O_TRUNC, 0644);
    if(fd1 == -1 || fd2 == -1) {
        perror("open error");
        exit(1);
    }

    int size = lseek(fd1, 0, SEEK_END);     // 获得文件大小
    if(pid == 0) {
        // 在子进程中，将位置偏移量调整到中间位置，形参空洞
        lseek(fd1, size/2, SEEK_SET);
        lseek(fd2, size/2, SEEK_SET);

    }
    else if(pid > 0) {
        // 在父进程中，将文件位置偏移量调整到开头处
        
        lseek(fd1, 0, SEEK_SET );
 
    }

    char buf[1024];
    int nread;

    while(1) {
        bzero(buf, 1024);     // 相当于 memset(buf,0x00,1024)
        nread = read(fd1, buf, 1024);
        if(nread == 0) {
            break;
        }

        if(pid > 0) {
            // 在父进程中，查看当前偏移量是否已经到达中间位置
            int n;
            n = lseek(fd1, 0, SEEK_CUR) - size/2;
            if(n >= 0) {
                // 达到中间位置或者超过中间位置
                write(fd2, buf, n);   // 写入未超过中间位置的字节
                exit(0);   // 写完之后退出
            }
        }
        write(fd2, buf, nread);
    }

    close(fd1);
    close(fd2);


    return 0;
}

