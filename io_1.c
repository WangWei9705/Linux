/**********************************************************
 * Author        : WangWei
 * Email         : 872408568@qq.com
 * Last modified : 2019-05-05 20:38
 * Filename      : IO_1.c
 * Description   : 标准IO函数的实现
 * fopen 、fclose   打开、关闭指定文件
 *
 * *******************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/ioctl.h>
#include <strings.h>

int main()
{
    FILE *fp = fopen("1.txt", "w+");    // FILE *fopen(const char *path, const char *mode);   指定文件  打开方式

    //文件打开失败，则fopen()返回NULL
    if(fp == NULL)  {

        perror("fopen error");
        exit(1);
    }

    char *buf[1024];
    FILE *fp_src = fp;

    bzero(buf, 1024);
     fwrite(buf,1024,12,fp_src);

     fread(buf,1024,12,fp_src);


    // 文件关闭失败，则fclose()返回EOF
    if(fclose(fp) == EOF) {
        perror("fclose error");
        exit(1);
    }

    
    return 0;
}

