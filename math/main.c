/**********************************************************
 * Author        : WangWei
 * Email         : 872408568@qq.com
 * Last modified : 2019-04-29 21:10:19
 * Filename      : main.c
 * Description   : 
 * *******************************************************/

#include <stdio.h>

#include "add.h"
#include "sub.h"
#include "mul.h"
#include "div.h"

int main()
{
    int a;
    int b;

    printf("请输入两个整数：");
    scanf("%d %d", &a, &b);

    printf("[add]:%d \n",add(a, b));
    printf("[sub]:%d \n",sub(a, b));
    printf("[mul]:%d \n",mul(a, b));
    printf("[div]:%d \n",div(a, b));

    return 0;
}

