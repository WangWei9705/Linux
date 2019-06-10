/**********************************************************
 * Author        : WangWei
 * Email         : 872408568@qq.com
 * Last modified : 2019-06-04 12:33:12
 * Filename      : tcpsocket.hpp
 * Description   : Tcp套接字编程的封装
 * *******************************************************/
#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <errno.h>
#include <iostream>
using namespace std;

#define CHECK_RET(q) if((q) == false) {return -1;}
class tcpsocket
{
public:
    tcpsocket()
    :_fd(-1)
    {}

    ~tcpsocket() {
        close(_fd);
    }
    // 1、创建套接字
    bool Socket() {
        _fd = socket(AF_INET,SOCK_STREAM, IPPROTO_TCP); 
        if(_fd < 0) {
            perror("socket errpr");
            return false;
        }
        return true;
    }

    // 为套接字绑定地址
    bool Bind(string &ip, uint16_t port) {
        struct sockaddr_in addr;
        addr.sin_family = AF_INET;
        addr.sin_port = htons(port);
        addr.sin_addr.s_addr = inet_addr(ip.c_str());
        socklen_t len = sizeof(struct sockaddr_in);
        int ret = bind(_fd, (struct sockaddr*)&addr, len);
        if(ret < 0) {
            perror("bind error");
            return false;
        }
        return true;
    }

    // 服务器开始监听
    bool Listen() {
        //  int listen(int sockfd, int backlog);
        //  baxklog ——正在等待连接的最大队列长度,
        //  backlog不能决定服务端能接收客户端的最大上限
        int ret = listen(_fd, 5);
        if(ret < 0) {
            perror("listen error");
            return false;
        }
        return true;
    }
    void SetFd(int fd) {
        _fd = fd;
    }

    // 接收链接请求
    bool Accept(tcpsocket &client, string &client_ip, uint16_t &client_port) {
    // int accept(int sockfd, struct sockaddr *addr, socklen_t *addrlen);
    // addr 监听到的客户端地址信息       addrlen 监听到的客户端的地址信息长度
        struct sockaddr_in addr;
        socklen_t len = sizeof(struct sockaddr_in);
        int ret = accept(_fd, (struct sockaddr*)&addr, &len);
        if(ret < 0) {
            perror("accept error");
            return false;
        }

        // 新的cockfd
        client.SetFd(ret);
        client_ip = inet_ntoa(addr.sin_addr);
        client_port = ntohs(addr.sin_port);
        return true;

    }

    // 建立连接
    bool Connect(string &server_ip, uint16_t server_port) {
        // int connect(int sockfd, const struct sockaddr *addr socklen_t addrlen);
        struct sockaddr_in addr;
        addr.sin_family = AF_INET;  // Ipv4
        addr.sin_port = htons(server_port);
        addr.sin_addr.s_addr = inet_addr(server_ip.c_str());
        socklen_t len = sizeof(struct sockaddr_in);

        int ret = connect(_fd, (struct sockaddr*)&addr, len);
        if(ret < 0) {
            perror("connect error");
            return false;
        }
        return true;

    }
    
    // 回复消息
    bool Recv(string &buf) {
        // ssize_t recv(int sockfd, void *buf, size_t len, int flags);
        // flag   0默认阻塞接收
        char temp[4096];
        int ret = recv(_fd, temp, 4096, 0);
        if(ret < 0) {
            perror("recv error");
            return false;
        } else if(ret == 0) {
            cout << "peer shutdown" << endl;
            return false;
        }
        buf.assign(temp,ret);  
        return true;
    }

    // 发送消息
    bool Send(string &buf) {
        // ssize_t send(int sockfd, const void *buf, size_t len, int flags);
        int ret = send(_fd, buf.c_str(), buf.size(), 0) ;
        if(ret < 0) {
            perror("send error");
            return false;
        }
        return true;
    }

    // 关闭连接
    bool Close() {
        close(_fd);
        return true;
    }
    

private:
    int _fd;

};

