/**********************************************************
 * Author        : WangWei
 * Email         : 872408568@qq.com
 * Last modified : 2019-06-27 22:32:59
 * Filename      : select.cpp
 * Description   : 封装select类并实现对tcp套接字的监控
 * *******************************************************/
#include "tcpsocket.hpp"
#include <sys/select.h>
#include <vector>


class Select {
public:
    Select():_maxfd(-1) {

        // 清空描述符集合
        FD_ZERO(&_rfd);
    }


    bool Add(tcpsocket &sock) {
        int fd = sock.GetFd();

        FD_SET(fd, &_rfd);

        _maxfd = _maxfd > fd ? _maxfd : fd;

        return true;
    }

    bool Del(tcpsocket &sock) {
        int fd = sock.GetFd();

        FD_CLR(fd, &_rfd);

        for(int i = _maxfd; i >= 0; i--) {
            // 判断fd是否还在集合中
            if(FD_ISSET(i, &_rfd)) {
                // 如果在，_maxfd = i;
                _maxfd = i;
                break;
            }
        }
        return true;
    }

    bool watch(vector<tcpsocket> &list, int timeout_sec = 5) {
        struct timeval tv;
        tv.tv_sec = timeout_sec;
        tv.tv_usec = 0;

        fd_set set = _rfd;
        //  int select(int nfds, fd_set *readfds, fd_set *writefds,
        //  fd_set *exceptfds, struct timeval *timeout);
        //
        int ret = select(_maxfd+1, &set, NULL, NULL, &tv);
        if(ret < 0) {
            perror("select error");
            return false;
        } else if(ret == 0) {
            cout << "select wait timeout" <<endl;
            return false;
        } else {
            for(int i = 0; i <= _maxfd; i++) {
                if(FD_ISSET(i, &set)) {
                    tcpsocket sock;
                    sock.SetFd(i);
                    list.push_back(sock);
                }
            }

        }
        return true;
    }

    
private:
    fd_set _rfd;
    int _maxfd;

};



int main() {
    tcpsocket sock;

    CHECK_RET(sock.Socket());
    CHECK_RET(sock.Bind("127.0.0.1", 9000));
    CHECK_RET(sock.Listen());
    Select s;
    s.Add(sock);
    while(1) {
        vector<tcpsocket> list;
        if(s.watch(list) == false) {
            continue;
        }

        for(size_t i = 0; i < list.size(); i++) {
            if(list[i].GetFd() == sock.GetFd()) {
                tcpsocket cli_sock;
                string ip;
                uint16_t port;

                if(sock.Accept(cli_sock, ip, port) == false) {
                    continue;
                }
                s.Add(cli_sock);

            } else {
                string buf;
                if(list[i].Recv(buf)) {
                    s.Del(list[i]);
                    list[i].Close();
                    continue;
                }
                cout << "client sys:" << buf;
            }

                
        }

    }
    return 0;
}
