/**********************************************************
 * Author        : WangWei
 * Email         : 872408568@qq.com
 * Last modified : 2019-04-28 16:50:59
 * Filename      : open.c
 * Description   :文件相关系统调用接口open/read/write/close的实现
 * int open(const char *pathname, int flags);   打开指定文件
 * pathname    文件名  
 * flags       选项标志   O_RDWR | O_CREAT | O_TRUNC | O_APPEND
 *                只能选其一/也必选其一
 *                O_RDONLY    只读
 *                O_WRONLY    只写
 *                O_RDWR      读写
 *                可选：
 *                O_CREAT     文件不存在则创建，存在则打开
 *                O_TRUNC     打开文件的时候清空原有内容
 *                O_APPEND    写数据的时候总是追加在文件末尾
 * mode        文件权限
 *                S_IWUSR | S_IXUSR|S_IRWXG.........
 *                0664
 * 返回值：文件描述符（正整数）    失败：-1   
 *
 * ssize_t read(int fd, void *buf, size_t count);          读取指定文件
 * fd    文件描述符
 * buf    定义的缓冲区
 * count  要读取的数据字节数
 *返回值：成功返回读取到字节数   失败：-1

 *  ssize_t write(int fd, const void *buf, size_t count);     往指定文件中写入数据
 * fd    文件描述符
 * buf    写入的内容
 * count   写入的字节数
 *返回值：成功时返回写入的字节数  失败：-1
 * int close(int fd);    关闭指定文件
 * fd    指定文件描述符          
 * 返回值：成功:0    失败：-1
 * *******************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>

int main()
{
  
    char* file = "1.txt";
    //   int open(const char *pathname, int flags, mode_t mode)
    umask(0);  // 设置默认权限掩码
    int fd = open(file , O_RDWR | O_CREAT , 0664);
    if(fd < 0) {
        perror("open error");
        return -1;
    }
    
    // ssize_t write(int fd, const void *buf, size_t count);
    char buf[1024] = "hello bit !";
    int ret = write(fd, buf , 1024);
    if(ret < 0) {
        perror("write error");
        return -1;
    }
    // off_t lseek(int fd, off_t offset, int whence);   重新定位读/写文件偏移量
    //  fd: 打开文件返回的操作句柄--文件描述符
    //  offset: 偏移量
    //  whence：偏移起始位置
    //      SEEK_SET
    //      SEEK_CUR
    //      SEEK_END
    //  返回值：偏移的位置到文件起始位置的偏移量
    lseek(fd, 0, SEEK_SET);


    memset(buf,0x00,1024);
    // ssize_t read(int fd, void *buf, size_t count);
   ret =  read(fd, buf, 1023);
   if(ret < 0) {
       perror("read error");
       return -1;
   }
   else if(ret == 0) {
       printf("have no date \n");
       return -1;
   }

   printf("buf:%d %s \n",ret,buf);
   close(fd);

    return 0;
}

