/**********************************************************
 * Author        : WangWei
 * Email         : 872408568@qq.com
 * Last modified : 2019-05-04 14:44:06
 * Filename      : mycopy.c
 * Description   : read 函数和 write 函数的应用，将一个指定文件中的内容复制到另一个文件中去
 * *******************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <fcntl.h>

#define SIZE 1024

int main( int argc, char **argv)
{
    int fd_from;
    int fd_to;

    if(argc != 3) {
        printf("Uage: %s <src> <dst>u\n", argv[0]);
        exit(1);
    }

    // 以只读方式打开源文件，以只写方式打开目录文件
    
    fd_from = open(argv[1], O_RDONLY);
    fd_to = open(argv[2], O_WRONLY | O_CREAT | O_TRUNC,0644);

    char buf [SIZE];
    char *p;
    int nread;
    int nwrite;

    while(1) {
        // 如果出错且错误码是EINTR，则循环再读
        while((nread = read(fd_from, buf, SIZE)) == -1
            && errno == EINTR) {
                ;
            }
        // 如果出错且错误码不是EINTR，则遇到真正的错误，退出
        if(nread == -1) {
            perror("read error");
            break;
        }

        if(nread == 0) {
            break;  // 读到文件末尾了，复制完成

        }

        p = buf;
        while(nread > 0) {
            // 如果出错且错误码是EINTR，则新欢再写
            while((nwrite = write(fd_to, p ,SIZE)) == -1
                  && errno == EINTR) {
                ;
            }


            // 否则辅导了真正的错误，直接退出
            
            if(nwrite == -1) {
                perror("write error");
                break;
            }

            nread -= nwrite; // nread 减去已经写入的nwrite
            p += nwrite;  // 调整写入数据的指针

        }
    }

    close(fd_from);
    close(fd_to);
    
    return 0;
}

