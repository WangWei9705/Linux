/**********************************************************
 * Author        : WangWei
 * Email         : 872408568@qq.com
 * Last modified : 2019-07-22 23:00:49
 * Filename      : daemom.cpp
 * Description   : 守护进程的实现
 * 步骤：1、创建子进程，同时父进程退出，是子进程尘能够为孤儿进程
 * 2、子进程调用setsid()脱离控制台控制
 * 3、使用chdir将当前目录改为"/"根目录脱离文件系统
 * 4、重置文件掩码，umask设置为0，取消任何文件的权限屏蔽
 * 5、关闭所有文件描述符
 * *******************************************************/
#include <iostream>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
using namespace std;


void create_daemom(void) {
    pid_t pid = 0;
    pid = fork();
    if(pid > 0) {
        cout << "parent exit()" << endl;
        exit(0);
    } else if(pid < 0) {
        perror("fork error");
        exit(-1);
    } else if(pid == 0) {
        // 调用setsid()脱离控制台
        pid = setsid();
        if(pid < 0) {
            perror("setsed error");
        }

        // 调用chdir脱离文件系统
        chdir("/");

        // 重置文件掩码
        umask(0);

        // 关闭所有文件描述符
        int i = sysconf(_SC_OPEN_MAX);   // 得到系统最大文件描述符
        for(; i > 0; i-- ) {
            close(i);
        }

        open("/dev/null", O_RDWR);   // 将0,1,2定位到dev/null
        open("/dev/null", O_RDWR);   // 将0,1,2定位到dev/null
        open("/dev/null", O_RDWR);   // 将0,1,2定位到dev/null

    }
}

int main()
{
    create_daemom();
    while(1) {
        cout << "create ok !" << endl;
        sleep(3);
    }
    return 0;
}

