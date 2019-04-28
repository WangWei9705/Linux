/**********************************************************
 * Author        : WangWei
 * Email         : 872408568@qq.com
 * Last modified : 2019-04-28 21:00:40
 * Filename      : shell.c
 * Description   : 使minishell支持输入/输出/追加重定向 
 * minishell实现步骤：
 *      1、获取标准输入
 *      2、解析得到的字符串
 *      3、创建子进程，进行程序替换
 *      4、父进程进行进程等待
 * *******************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <ctype.h>
#include <string.h>
int main()
{
    char buf[1024] = {0};
    while(1) {
        printf("[user@locahost]$");
        fflush(stdout);

        memset(buf,0x00,1024);

        if(scanf("%[^\n]%*c",buf) != 1) { 
        // ^表示"非"，[^\n]表示读入换行字符就结束读入。这个是scanf的正则用法，我们都知道scanf不能接收空格符，但是使用%[^\n]就可以了。
       // *表示该输入项读入后不赋予任何变量，即scanf("%*[^\n]%*c")表示跳过一行字符串。
            getchar();
            continue;
        }

        // 创建子进程
        int pid = fork();
        if(pid < 0) {
            perror("fork error");
            return -1;
        }
        else if(pid == 0){
            char *str = buf;
            int count = 0;  // 重定向符号个数
            char *file = NULL;
            int fd = 0;

            // 找重定向个数
            while(*str != '\0') {

                if(*str == '>') {
                    count++;
                    *str = '\0';
                    
                    if(*(str + 1) == '>') {
                        count++;

                    }
                    str += count;

                    while(*str != '\0' && !isspace(*str)) {
                        *str++ = '\0';
                    }

                    file = str;

                    // 走完文件
                    while(*str != '\0' && !isspace(*str)) {
                        str++;
                    }
                    *str = '\0';
                    continue;
            }
                str++;
        }
            if(count == 1) {
                fd = open(file, O_CREAT | O_WRONLY | O_TRUNC, 0664);
             
                // int dup2(int fd1, int fd2)   
                // 用dup2则可以用fd2参数指定新的描述符数值。
                // 如果fd2已经打开，则先关闭。若fd1=fd2，则dup2返回fd2，而不关闭它。
                dup2(fd,1);
            }
            else if(count == 2) {
                  fd = open(file, O_CREAT | O_WRONLY | O_TRUNC, 0664);
                  dup2(fd,1);
            }

            // 解析外部命令
            char *ptr = buf;
            char *argv[64];
            int argc = 0;
            while(*ptr != '\0') {
                if(!isspace(*ptr)) {
                    argv[argc++] = ptr;
                    while(*ptr != '\0' && !isspace(*ptr)) {
                        ptr++;
                    }
                }
                *ptr = '\0';
                ptr++;
            }
            argv[argc] = NULL;

            //子进程进行程序替换
            //  int execvp(const char *file ,char * const argv []);
            //  execvp()会从PATH 环境变量所指的目录中查找符合参数file 的文件名，
            //  找到后便执行该文件，然后将第二个参数argv传给该欲执行的文件。
            execvp(argv[0], argv);
            exit(0);
    }
        waitpid(pid, NULL, 0);
    }
    printf("Hello world\n");
    return 0;
}

