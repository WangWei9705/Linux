/**********************************************************
 * Author        : WangWei
 * Email         : 872408568@qq.com
 * Last modified : 2019-06-22 22:19:56
 * Filename      : read.c
 * Description   : 系统IO接口——读
 * *******************************************************/
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

int main()
{
    int fd = open("test.txt", O_RDONLY);
    if(fd < 0) {
        perror("open error");
        return 1;
        
    }

    const char *msg = "晚上好！\n";

    char buf[1024];

    while(1) {
        ssize_t s = read(fd, buf, strlen(msg));
        if(s > 0) {
            printf("%s", buf);
        } else {
            break;
        }
    }
    close(fd);
    printf("Hello world\n");
    return 0;
}

