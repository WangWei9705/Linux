#include <stdio.h>
#include <string.h>
#include <unistd.h>

int main()
{
    int n = 0;          // 进度数字
    char bar[1024];    // 用来存放'#' 符号
    const char* label = "|\\-/";   // 末尾的一个旋转   
    // 将bar的空间初始化为0
    memset(bar,0,sizeof(bar));              // 函数原型：void *memset(void *s, int c, size_t n);

    while(n <= 100){
        printf("\033[35m[%-100s]\033[0m[%d%%][%c]\r", bar, n, label[n % 4]);
        fflush(stdout);
        bar[n++] = '#';
        usleep(100000);     // 睡眠0.1秒
    }
    printf("\n");
    return 0;
}

