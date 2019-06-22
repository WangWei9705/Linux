/**********************************************************
 * Author        : WangWei
 * Email         : 872408568@qq.com
 * Last modified : 2019-06-22 22:05:20
 * Filename      : write.c
 * Description   : 系统IO接口——写 
 * *******************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>


int main()
{
    umask(0);   // 设置默认权限
    int fd = open("test.txt", O_WRONLY | O_CREAT, 0644);
    if(fd < 0) {
        perror("open");
        return -1;
    }

    int count = 10;
    const char *msg = "你好呀！\n";
    int len = strlen(msg);

    while(count--) {
        write(fd, msg, len);
    }
    close(fd);
    printf("Hello world\n");
    return 0;
}

