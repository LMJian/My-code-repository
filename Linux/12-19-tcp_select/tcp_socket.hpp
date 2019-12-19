#pragma once
#include<iostream>
#include<stdio.h>
#include<string>
#include<unistd.h>
#include<unistd.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
using namespace std;

class TcpSocket
{
public:
    TcpSocket()
    :fd_(-1)
    {
        
    }

    TcpSocket(int fd)
    :fd_(fd)
    {

    }

    bool Socket()
    {
        //SOCK_STREAM代表tcp，是面向字节流的
        fd_=socket(AF_INET,SOCK_STREAM,0);
        if(fd_<0)
        {
            return false;
        }
        return true;
    }

    //给服务器使用的
    bool Bind(const string& ip,uint16_t port)
    {
        sockaddr_in addr;
        addr.sin_family=AF_INET;
        addr.sin_addr.s_addr=inet_addr(ip.c_str());
        addr.sin_port=htons(port);
        int ret=bind(fd_,(sockaddr*)&addr,sizeof(addr));
        if(ret<0)
        {
            perror("bind");
            return false;
        }
        return true;
    }

    //进入监听状态int listen(int sockfd,int backlog);
    //scokfd:fd_; backlog:表示操作系统内核队列里已经创建好的连接的个数，即队列长度
    //给服务器使用的
    bool Listen()
    {
        int ret=listen(fd_,30);
        if(ret<0)
        {
            perror("listen");
            return false;
        }
        return true;
    }

    //把连接队列中的链接取出一个到户代码中,如果队列中没有连接，默认就会阻塞
    //int accept(int sockfd,struct sockaddr* addr,socklen_t *addrle),addrle:是一个输入输出型参数
    //addr:对端IP地址和端口号;addrle:是一个输入输出型参数;返回值也是一个socket
    //给服务器使用的
    bool Accept(TcpSocket* peer,string* ip=NULL,uint16_t* port=NULL)
    {
        sockaddr_in peer_addr;
        socklen_t len=sizeof(peer_addr);

        //client_sock:也是一个socket
        int client_sock = accept(fd_,(sockaddr*)&peer_addr,&len);
        if(client_sock<0)
        {
            perror("client_sock");
            return false;
        }
        //输出型参数peer，ip,port,方便客户端使用，把对端的fd,IP,port情况返回
        peer->fd_=client_sock;
        if(ip!=NULL)
        {
            *ip=inet_ntoa(peer_addr.sin_addr);
        }
        if(port!=NULL)
        {
            *port=ntohs(peer_addr.sin_port);
        }
        return true;
    }


    //给服务器和客户端使用的
    int Recv(string* msg)
    {
        msg->clear();
        char buf[1024*10]={0};
        //recv的返回值：读取成功，返回结果为读到的字节数；如果读取失败，返回结果为-1，如果对端关闭了socket，返回结果为0；
        ssize_t n = recv(fd_,buf,sizeof(buf)-1,0);
        if(n<0)
        {
            perror("recv");
            return -1;
        }
        else if(n==0)
        {
            //需要考虑返回0的情况
            return 0;
        }
        else
        {
            //把读到buf中的内容复值到msg中
            msg->assign(buf);
            return 1;
        }
    }

    //给服务器和客户端使用的
    bool Send(const string& msg)
    {
        ssize_t n= send(fd_,msg.c_str(),msg.size(),0);
        if(n<0)
        {
            perror("send");
            return false;
        }
        return true;
    }

    //给客户端使用的
    bool Connect(const string& ip,uint16_t port)
    {
        sockaddr_in addr;
        addr.sin_family=AF_INET;
        addr.sin_addr.s_addr=inet_addr(ip.c_str());
        addr.sin_port=htons(port);

        int ret=connect(fd_,(sockaddr*)&addr,sizeof(addr));
        if(ret<0)
        {
            perror("connect");
            return false;
        }
        return true;
    }

    bool Close()
    {
        if(fd_!=-1)
        {
            close(fd_);
        }
        return true;
    }

    int GetFd()const
    {
        return fd_;
    }

private:
int fd_;
};
