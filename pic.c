// 代码说明子进程是父进程的拷贝，二者共用一块地址空间，但是该地址是虚拟地址，且二者的输出变量不同
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

int g_val = 0;    // 定义一个全局变量

int main()
{
    int pid = fork();
    if(pid < 0){
        perror("fork error");
        return 1;
    }
    else if(pid == 0) {
        g_val = 100;
        printf("child[%d] :%d : %p\n",getpid(), g_val, &g_val);
    }
    else{
        sleep(1);

        printf("father[%d]:%d:%p \n",getpid(), g_val,&g_val);
    }

    return 0;
}

