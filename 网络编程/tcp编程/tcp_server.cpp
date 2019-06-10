/**********************************************************
 * Author        : WangWei
 * Email         : 872408568@qq.com
 * Last modified : 2019-06-10 20:17:37
 * Filename      : tcp_server.cpp
 * Description   : 基于封装的TCP套接字服务端的实现
 * *******************************************************/
#include "tcpsocket.hpp"
int main(int argc,  char* argv[]) 
{
    if(argc != 3) {
        cout << "./tcp_sercer 172.17.35.247 9000" << endl;
        return -1;
    }
    string ip = argv[1];
    uint16_t port = atoi(argv[2]);

    tcpsocket server_sock;

    // 创建套接字
    CHECK_RET(server_sock.Socket());
    // 为套接字绑定地址
    CHECK_RET(server_sock.Bind(ip, port));
    // 开始监听
    CHECK_RET(server_sock.Listen());
    // 开始数据传输
    while(1) {
        tcpsocket client_sock;
        string client_ip;
        uint16_t clinet_port;
        // 如果没有新的客户端接入则继续传输数据
        if(server_sock.Accept(client_sock, client_ip, clinet_port) == false) {
            continue;
        }

        cout << "New Client:" << client_ip << clinet_port << endl;

        string buf;
        client_sock.Recv(buf);
        cout << "Client say:" << buf << endl;

        buf.clear();
        cout << "server say:";
        fflush(stdout);
        cin >> buf;
        client_sock.Send(buf);
    }
    server_sock.Close();
    return 0;
}

