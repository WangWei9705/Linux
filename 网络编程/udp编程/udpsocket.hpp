/**********************************************************
 * Author        : WangWei
 * Email         : 872408568@qq.com
 * Last modified : 2019-05-26 16:21
 * Filename      : udpsocket.hpp
 * Description   :  封装UdpSocket
 * *******************************************************/
#pragma once

#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include <string>

#include <sys/socket.h>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <iostream>
using namespace std;

class UdpSocket {
public:
    UdpSocket():fd(-1) {

    }
    // 1、创建套接字
    // int socket(int domain, int type, int protocol);
    bool CreatSocket() {
        fd = socket(AF_INET ,SOCK_DGRAM, 0);
        if(fd < 0) {
            perror("CreatSocket error");
            return false;
        }
        return true;
    }
    // 2、为套接字绑定地址
    // int bind(int sockfd, const struct sockaddr *addr,socklen_t addrlen);
    bool Bind(const string& ip, uint16_t port) {
        struct sockaddr_in addr;
        addr.sin_family = AF_INET;
        addr.sin_addr.s_addr = inet_addr(ip.c_str());   
        addr.sin_port = htons(port);
        int ret = bind(fd, (struct sockaddr*)&addr, sizeof(addr));
        if(ret < 0) {
            perror("Bind error");
            return false;
        }
        return true;

    }
    // 3、接收数据
    // ssize_t recvfrom(int sockfd, void *buf, size_t len, int flags,struct sockaddr *src_addr, socklen_t *addrlen);
    bool Recvfrom(string* buf, string* ip = NULL, uint16_t* port = NULL) {
        char tmp[1024] = {0};
        struct sockaddr_in addr;
        size_t recv = recvfrom(fd, tmp, sizeof(tmp) - 1, 0, (struct sockaddr*)&addr, (socklen_t *)sizeof(addr));

        if(recv < 0) {
            perror("Recvfrom error");
            return false;
        }
        // 将读到的数据放到输出参数中
        buf->assign(tmp, recv);
        if(ip != NULL) {
            *ip = inet_ntoa(addr.sin_addr);    
        }
        if(port != NULL) {
            *port = ntohs(addr.sin_port);
        }
        return true;
        
    }
    // 4、发送数据
    // ssize_t sendto(int sockfd, const void *buf, size_t len, int flags,const struct sockaddr *dest_addr, socklen_t addrlen);
    bool SendToco(const string& buf, const string& ip, uint16_t port) {
        struct sockaddr_in addr;
        addr.sin_family = AF_FILE;
        addr.sin_addr.s_addr = inet_addr(ip.c_str());
        addr.sin_port = htons(port);
        ssize_t Send = sendto(fd, buf.data(), buf.size(), 0, (struct sockaddr*)& addr, sizeof(addr));

        if(Send < 0) {
            perror("Send error");
            return false;
        }
        return true;

    }
    // 5\关闭套接字
    // int close(int fd);
    bool Close() {

        close(fd);
        return true;
    }
private:
    int fd ;
};
