#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(){
    char *env;
    const char* envname = "vim";
    // 获取变量vim的环境变量
    env = getenv(envname);
    printf("The first env %s = %s \n ",envname,env);

    // 设置环境变量
    setenv(envname, "I will get it !",1);
    printf("The second env %s = %s \n",envname, env);

    env = getenv(envname);
    printf("The third env %s = %s ",envname, env);

    // 删除环境变量
    
    int ret = unsetenv(envname);
    printf("ret %d \n",ret);

    env = getenv(envname);
    printf("The third env %s = %s \n",envname, env);

    return 0;
}
