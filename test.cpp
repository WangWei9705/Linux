/**********************************************************
 * Author        : WangWei
 * Email         : 872408568@qq.com
 * Last modified : 2019-04-30 23:58:25
 * Filename      : test.cpp
 * Description   : 指针和引用的区别
 * 引用实际上就是实体的一个别名，与实体共用同一块内存空间
 * 使用在底层中是按照指针的方式进行处理的
 * 区别：
 * 引用必须初始化，指针不要求
 * 引用一旦绑定实体就不可以修改，指针随时可以修改
 * 引用不能为NULl指针可以
 * 引用不存在多级引用，指针有多级指针
 * 引用比指针更安全
 * 引用自增自减是实体的自增自减，指针则是指针偏移一个类型
 * *******************************************************/
#include <iostream>

void swap(int& a, int& b) {
    int temp = a;
    a = b;
    b = temp;
}


int main()
{
    int a =10;
    int *pa =NULL;
    swap(a,*pa);

    std::cout << a << std::endl;
    std::cout<< *pa << std::endl;
    return 0;
}

