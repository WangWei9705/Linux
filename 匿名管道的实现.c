#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>    // 用于创建匿名管道


int main(){
    int fds[2];
    char buf[100];
    int len;

    // 创建匿名管道
    if(pipe(fds) == -1){
        printf("创建失败！\n");
        perror("make pipe");
        exit(1);
    }

    // 从标准输入中读取数据
    while(fgets(buf,100,stdin)) {
        len = strlen(buf);

        // fd[0]  表示读端   fd[1]     表示写端
        // 将数据写入到管道中
        if( write(fds[1], buf ,len ) != len) {
            perror("write to pipe");
            break;
        }
        memset(buf, 0x00, sizeof(buf));

        // 从管道中读取数据
        if((len = read(fds[0], buf, 100)) == -1) {
            perror("read from pipe");
            break;
        }

        // 往标准输出写数据
        
        if(write(1, buf, len) != len) {
            perror("write to stdout");
            break;
        }

    }
}