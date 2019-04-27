// 通过第三方变量environ获取环境变量
#include <stdio.h>

int main(int argc, char* argv[]) {
    int i = 0;
    // libc中定义的全局变量environ指向环境变量表,environ没有包含在任何头文件中,所以在使用时 要用extern声明。
    extern char** environ;
    for(i = 0; environ[i]; i++) {
        printf("%s \n",environ[i]);
        
    }
    return 0;

}

