/**********************************************************
 * Author        : WangWei
 * Email         : 872408568@qq.com
 * Last modified : 2019-06-22 21:41:39
 * Filename      : read.c
 * Description   : 标准IO接口——读
 * *******************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
    FILE* fp = fopen("Linux.txtx", "r");
    if(!fp) {
        printf("fopen error \n");
    }

    char buf[1024];

    const char *msg = "我爱学习！\n";

    while(1) {
        ssize_t s = fread(buf, 1, strlen(msg), fp);
        if(s > 0) {
            buf[s] = 0;
            printf("%s", buf);
            break;
        }
    }
    fclose(fp);
    printf("Hello world\n");
    return 0;
}

