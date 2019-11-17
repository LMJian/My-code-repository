#pragma once
#include<iostream>
#include<cstdio>
#include<cstring>
#include<string>
#include<unistd.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
using namespace std;

class TcpSocket{
  public:
    TcpSocket()
      :_fd(-1)
    {}

    bool Socket(){
      _fd=socket(AF_INET,SOCK_STREAM,0);
      if(_fd<0)
      {
        perror("socket");
        return false;
      }
      return true;
    }
    //给服务器使用
    bool Bind(const string& ip,uint16_t port){
      sockaddr_in addr;
      addr.sin_family=AF_INET;
      addr.sin_addr.s_addr=inet_addr(ip.c_str());
      addr.sin_port=htons(port);
      int ret=bind(_fd,(sockaddr*)&addr,sizeof(addr));
      if(ret<0){
        perror("bind");
        return false;
      }
      return true;
    }
    //给服务器使用
    bool Listen(){
      int ret=listen(_fd,10);
      if(ret<0){
        perror("listen");
        return false;
      }
      return true;
    }
    //给服务器使用
    bool Accept(TcpSocket* peer,string* ip=NULL,uint16_t* port=NULL){
      //从链接队列中取一个链接到用户代码
      //如果队列没有链接，就会阻塞
      sockaddr_in peer_addr;
      socklen_t len=sizeof(peer_addr);
      //返回值也是一个socket
      int client_sock=accept(_fd,(sockaddr*)&peer_addr,&len);
      if(client_sock<0){
        perror("accept");
        return false;
      }
      peer->_fd=client_sock;
      if(ip!=NULL){
        *ip=inet_ntoa(peer_addr.sin_addr);
      }
      if(port!=NULL){
        *port=ntohs(peer_addr.sin_port);
      }
      return true;
    }
    //客户端和服务器都会使用
    int Recv(string* msg){
      msg->clear();
      char buf[1024*10]={0};
      int n=recv(_fd,buf,sizeof(buf)-1,0);
      //recv返回值：读取成功返回字节数，失败返回-1
      //如果对端关闭了socket返回结果为0
      if(n<0){
        perror("recv");
        return -1;
      }else if(n==0){
        //考虑返回0的情况
        return 0;
      }
      msg->assign(buf);
      return 1;
    }
    //服务器和客户端都会使用
    bool Send(const string& msg){
      int n=send(_fd,msg.c_str(),msg.size(),0);
      if(n<0){
        perror("send");
        return false;
      }
      return true;
    }
    //客户端使用
    bool Connect(const string& ip,uint16_t port){
      sockaddr_in addr;
      addr.sin_family=AF_INET;
      addr.sin_addr.s_addr=inet_addr(ip.c_str());
      addr.sin_port=htons(port);
      int ret=connect(_fd,(sockaddr*)&addr,sizeof(addr));
      if(ret<0){
        perror("connect");
        return false;
      }
      return true;
    }
    bool Close(){
      if(_fd!=-1){
        close(_fd);
      }
      return true;
    }
  private:
    int _fd;
};
