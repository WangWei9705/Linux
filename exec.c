// exec()函数族:在进程中加载新的程序文件或脚本，覆盖原有代码，重新运行
// 使用exec函数族主要有两种情况：
// (1)当进程认为自己不能再为系统和用户做出任何贡献时，就可以调用exec函数族中的任意一个函数让自己重生。
// (2)如果一个进程想执行另一个程序，那么它就可以调用fork函数新建一个进程，然后调用exec函数族中的任意一个函数，这样看起来就像通过执行应用程序而产生了一个新进程(这种情况非常普遍)。
// exec函数族共有6种不同形式的函数。这6个函数可以划分为两组：
// (1)execl、execle和execlp。
// (2)execv、execve和execvp。
// 这两组函数的不同在于exec后的第一个字符，第一组是l，在此称，为execl系列；第二组是v，在此称为execv系列。这里的l是list(列表)的意思，表示exec1系列函数需要将每个命令行参数作为函数的参数进行传递；而v是vector(矢量)的意思，表示execv系列函数将所有函数包装到一个矢量数组中传递即可。
// exec函数的原型如下：
// int execl(const char * path，const char * arg，…)；
// int execle(const char * path，const char * arg，char * const envp[])；
// int execlp(const char * file，const char * arg，…)；
// int execv(const char * path，char * const argv[])；
// int execve(const char * path，char * const argv[]，char * const envp[])；
// int execvp(const char * file，char * const argv[])；
// 参数说明：
// path：要执行的程序路径。可以是绝对路径或者是相对路径。在execv、execve、execl和execle这4个函数中，使用带路径名的文件名作为参数。
// file：要执行的程序名称。如果该参数中包含“/”字符，则视为路径名直接执行；否则视为单独的文件名，系统将根据PATH环境变量指定的路径顺序搜索指定的文件。
// argv：命令行参数的矢量数组。
// envp：带有该参数的exec函数可以在调用时指定一个环境变量数组。其他不带该参数的exec函数则使用调用进程的环境变量。
// arg：程序的第0个参数，即程序名自身。相当于argv[O]。
// …：命令行参数列表。调用相应程序时有多少命令行参数，就需要有多少个输入参数项。注意：在使用此类函数时，在所有命令行参数的最后应该增加一个空的参数项(NULL)，表明命令行参数结束。
// 返回值：一1表明调用exec失败，无返回表明调用成功

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
    pid_t pid = fork();


    if(pid > 0) {
        // 父进程
        printf("parent[%d] \n",getpid());
        exit(0);
    }

    if(pid == 0) {
        // 子进程
        printf("child[%d] \n",getpid());
        execl("./proce", "proce", NULL);   // 执行setenv程序
        printf("这是一条将被覆盖的代码！\n");
    

    }

    return 0;
}
