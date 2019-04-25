// eixt and _exit 函数的使用及对比
//  void exit(进程的返回值)   void _exit(进程的返回值)     无返回值
// 如果子进程正常退出 status = 0    异常退出为非0
// exii()退出时，会自动冲洗标准I/O残留的数据到内核


#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

// 进程退出处理函数
void routine1() {
    printf("routine1 is called \n");

}

void routine2() {
    printf("routine2 is called \n");
}


int main()
{
    atexit(routine1);   //  注册退出处理函数
    atexit(routine2);

    fprintf(stdout ,"fjkfgkj");   // 将数据传输到标准缓冲区
    
#ifdef _EXIT
    _exit(0);   // 直接退出
#else 
    exit(0);    // 冲洗缓冲区数据，并执行退出处理函数
#endif
    return 0;
}

