// 通过系统调用中的getenv函数来获取环境变量
#include <stdio.h>
#include <stdlib.h>

int main()
{
    printf("%s \n",getenv("PATH"));
    return 0;
}

