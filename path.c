// 命令行第三个参数获取环境变量
#include <stdio.h>

int main(int arc, char* argv, char* env[])
{
    int i = 0;

    for(i = 0; env[i];i++) {
        printf("%s \n",env[i]);
    }
    return 0;
}

