/**********************************************************
 * Author        : WangWei
 * Email         : 872408568@qq.com
 * Last modified : 2019-05-04 15:01
 * Filename      : lseek.c
 * Description   : lseek 函数的实现
 * 函数原型：  off_t lseek(int fd, off_t offset, int whence);
 * 参数说明:    fd  要调整让那个位置偏移量的文件的描述符
 *              offset 新位置偏移量相对基准点的偏移
 *              whebce 基准点
 *					  SEEK_SET    	文件开头处
				      SEEK_CUR  	当前位置
     				  SEEK_END   	文件结尾
返回值：	成功	新文件位置偏移量	失败	-1
 * *******************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>


int main()
{
    int fd = open("1.txt", O_RDWR | O_CREAT | O_TRUNC, 0644);

    write(fd, "新年快乐！" ,15);  
    lseek(fd, 100, SEEK_CUR);   // 定位到100个字节之后
    write(fd, "hello word", 15);


    close(fd);
    return 0;
}

