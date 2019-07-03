/**********************************************************
 * Author        : WangWei
 * Email         : 872408568@qq.com
 * Last modified : 2019-07-03 14:18:11
 * Filename      : epoll.cpp
 * Description   : 基于tcpsocket封装的epoll类接口 
 * *******************************************************/
#include "tcpsocket.hpp"
#include <vector>
#include <sys/epoll.h>
#define MAXEVENTS 10
class Epoll {
public:
    bool create() {
        _epfd = epoll_create(1);
        if(_epfd < 0) {
            perror("create error");
            return false;
        }
        return true;
    }
    bool Add(tcpsocket &sock) {
        // int epoll_ctl(int epfd,int op,int fd,struct epoll_event *event);
        int fd = sock.GetFd();
        struct epoll_event ev;   // 定义一个结构体用来描述事件结构信息
        ev.data.fd = fd;    // fd是要监控的描述符
        ev.events = EPOLLIN;   // 要监控的事件  这里设置为可写 
        int ret = epoll_ctl(_epfd, EPOLL_CTL_ADD, fd, &ev);
        if(ret < 0) {
            perror("epoll add error");
            return false;
        }
        return true;
    }
    bool Del(tcpsocket &sock) {
        int fd = sock.GetFd();
        int ret = epoll_ctl(_epfd, EPOLL_CTL_DEL, fd, NULL);
        if(ret < 0) {
            return false;
        }
        return true;
    }
    bool Wait(vector<tcpsocket> &list, int time_msec = 3000) {
        // int epoll_wait(int epfd, struct epoll_eventint maxevents, 
        //                  int timeout);int maxevents, int timeout)
        struct epoll_event evs[MAXEVENTS]; 
        int nfds = epoll_wait(_epfd, evs, MAXEVENTS,time_msec);
        if(nfds < 0) {
            perror("epoll wait error");
            return false;
        } else if(nfds == 0) {
            cout << "epoll wait timeout" << endl;
            return false;
        }
        // 将就绪事件描述符添加的双向链表list中
        for(int i = 0; i < nfds; i++) {
            tcpsocket sock;
            sock.SetFd(evs[i].data.fd);
            list.push_back(sock);
        }
        return true;
    }

private:
    int _epfd;
};
int main()
{
    tcpsocket Epoll_sock;
    CHECK_RET(Epoll_sock.Socket());
    CHECK_RET(Epoll_sock.Bind("0.0.0.0", 9000));   // 0.0.0.0   表示任意地址
    CHECK_RET(Epoll_sock.Listen());

    Epoll epoll;
    CHECK_RET(epoll.create());
    CHECK_RET(epoll.Add(Epoll_sock));
    while(1) {
        vector<tcpsocket> list;
        bool ret = epoll.Wait(list, 5000);
        if(ret == false) {
            continue;
        }
        for(size_t i = 0; i < list.size(); i++) {
            if(Epoll_sock.GetFd() == list[i].GetFd()) {

                tcpsocket cli_sock;
                string cli_ip;
                uint16_t cli_port;
                ret =  Epoll_sock.Accept(cli_sock, cli_ip, cli_port);
                if(ret == false) {
                    continue;
                }

                epoll.Add(cli_sock);
            } else {
                string buf;
                ret = list[i].Recv(buf);
                if(ret == false) {
                    epoll.Del(list[i]);
                    list[i].Close();
                    continue;
                }

                cout << "client say:" << buf << endl;

            }
            


        }
    }

    Epoll_sock.Close();
    return 0;
}

