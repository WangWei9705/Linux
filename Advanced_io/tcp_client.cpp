/**********************************************************
 * Author        : WangWei
 * Email         : 872408568@qq.com
 * Last modified : 2019-06-10 20:28:36
 * Filename      : tcp_client.cpp
 * Description   : 基于封装的tcp桃姐客户端的实现
 * *******************************************************/
#include "tcpsocket.hpp"
#include <signal.h>
void sigcb(int signo) {
    cout << "connection closed" << endl;
}
int main(int argc, char* argv[]) {
    if(argc != 3) {
        cout << "./tcp_client 127.0.0.1 9000" << endl;
        return -1;
    }
    string ip = argv[1];
    uint16_t port = atoi(argv[2]);

    signal(SIGPIPE,sigcb);
    tcpsocket client_sock;

    // 创建套接字
    CHECK_RET(client_sock.Socket());
    // 绑定地址信息，客户端不建议手动绑定
    // 开始请求建立连接
    CHECK_RET(client_sock.Connect(ip, port));

    // 开始进行数据交换
    while(1) {
        string buf;
        cout << "client say:";
        fflush(stdout);
        cin >> buf;
        client_sock.Send(buf);

    }
    client_sock.Close();
    return 0;
}

