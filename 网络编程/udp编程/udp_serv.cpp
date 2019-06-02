/**********************************************************
 * Author        : WangWei
 * Email         : 872408568@qq.com
 * Last modified : 2019-06-02 21:29:37
 * Filename      : udp_serv.cpp
 * Description   : 基于udp封装的套接字编程服务端的实现
 * 1、创建套接字
 * 2、绑定套接字地址
 * 3、接收数据
 * 4、发送数据
 * 5、关闭套接字
 * *******************************************************/
#include "udpsocket.hpp"


int main(int argc, char* argv[]) {
    if(argc != 3) {
        cout << "./udp_serv ip port" <<endl;
        return -1;
    }

    string serv_ip = argv[1];
    uint16_t serv_port = atoi(argv[2]);

    UdpSocket serv_socket;

    CHECK_RE(serv_socket.CreatSocket());
    CHECK_RE(serv_socket.Bind(serv_ip, serv_port));

    // 开始循环接收、发送数据
    while(1) {
        string cli_ip;
        uint16_t cli_port;
        string buf;
        serv_socket.Recvfrom(buf, cli_ip, cli_port);    // 接收到来自客户端的数据
        cout << "ip:" << cli_ip.c_str() << "port:" << cli_port <<endl;
        cout << "clint say:" << buf.c_str() << endl;

        buf.clear();   // 清空缓冲区,以便能够往缓冲区中放数据
        cout << "server say:" ;
        fflush(stdout);   // 刷新标准输出
        cin >> buf;
        serv_socket.SendTo(buf, cli_ip, cli_port);   // 给客户端回复消息
    }
    // 通话结束后，关闭套接字
    serv_socket.Close();
    return 0;
}
