/* minishell 的实现
 *  1、获取标准输入，解析字符串等到命名
 *  2、判断命令是否重建
 *  3、创建子进程，让子进程背锅
 *  4、父进程进行进程等待
 * */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <fcntl.h>
#include <string.h>

char buf[1024] = { 0 };

int do_face()
{
    memset(buf,0,1024); // 将buf中的1024个字节初始化为0x00
    printf("[user@localhost]$");
    fflush(stdout);    // 刷新标准输出的缓冲区
    
    if(scanf("%[^\n]%c", buf) !=1)
    {
        getchar();
        return -1;
    }
    return 0;
}

int argc=0;
char* argv[64];

int do_prase()
{
    argc = 0;
    char* ptr=buf;
    while(ptr !='\0')
    {
        if(!isspace(*ptr))
        {
            argv[argc]=ptr;
            argc++;
            while(!isspace(*ptr) && *ptr!='\0')
            {
                ptr++;
            }
            *ptr='\0';
        }
        ptr++;
    }
    argv[argc]=NULL;
    return 0;

}


int main()
{

    while(1)
    {
        if(do_face() < 0)
        {
            continue;
        }

        if(do_prase()<0)
        {
            continue;

        }

        // 实现shell，功能
        
        if(strcmp(argv[0],"cd")==0)
        {
            // 改变工作路径
            chdir(argv[1]);
            continue;
            
        }

        // 创建子进程
        int pid =fork();
        if(pid <0)    // 创建失败
        {
            perror("fork error");
            return -1;

        }
        else if(pid ==0)   // 创建成功
        {
            // 在子进程中重定向
            int i=0;
            for(i =0 ;i < argc ;i++)
            {
                if(strcmp(argv[i], ">") == 0)
                {
                    int fd = open(argv[i+1], O_WRONLY | O_CREAT | O_TRUNC );
                    dup2(fd ,1);
                    argv[i] = NULL;

                }
                else if(strcmp(argv[i] , ">>") == 0)
                {
                    int fd = open(argv[i+1], O_WRONLY | O_CREAT | O_TRUNC );
                    dup2(fd ,1);
                    argv[i] = NULL;
                    
                }

            }
            execvp(argv[0] , argv);
            exit(-1);

        }
        wait( NULL );


    }
    return 0;
}

