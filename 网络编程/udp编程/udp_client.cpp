/**********************************************************
 * Author        : WangWei
 * Email         : 872408568@qq.com
 * Last modified : 2019-06-02 21:55:31
 * Filename      : udp_client.cpp
 * Description   : 基于udp封装的套接字编程客户端的实现
 * 1、创建套接字
 * 2、客户端不建议手动绑定套接字地址，这一步由操作系统自动完成
 * 3、给服务端发送数据
 * 4、从服务端得到回复
 * 5、通话结束，关闭套接字
 * *******************************************************/
#include "udpsocket.hpp"


int main(int argc, char* argv[]) {

    // 如果缓冲区中的argc不足3，则按照以下格式输入ip和端口
    if(argc != 3) {
        cout << "./udp_cli ip port" <<endl;
        return -1;
    }

    string serv_ip = argv[1];
    uint16_t serv_port = atoi(argv[2]);

    UdpSocket cli_socket;

    CHECK_RE(cli_socket.CreatSocket());
    // 客户端不建议手动绑定地址
    
    while(1) {
        string buf;
        cout << "client say:";
        fflush(stdout);
        cin >> buf;
        cli_socket.SendTo(buf,serv_ip, serv_port);

        // 清空缓冲区准备从服务端得到回复
        buf.clear();
        cli_socket.Recvfrom(buf,serv_ip,serv_port);
        cout << "servert say:" << buf << endl;
    }

    cli_socket.Close();
    return 0;
}
