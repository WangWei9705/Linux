/**********************************************************
 * Author        : WangWei
 * Email         : 872408568@qq.com
 * Last modified : 2019-06-22 21:34:36
 * Filename      : write.c
 * Description   : 标准IO接口——写
 * *******************************************************/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main()
{
    FILE* fp = fopen("Linux.txtx", "w");
    if(!fp) {
        printf("fopen error!\n");
    }

    const char* msg = "你好!\n";
    int count = 10;

    while(count--) {
        fwrite(msg, strlen(msg), 1, fp);
    }

    fclose(fp);
    return 0;
}

