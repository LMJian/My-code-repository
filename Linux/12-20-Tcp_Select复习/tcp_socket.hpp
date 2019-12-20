#pragma once
#include<iostream>
#include<sys/types.h>
#include<sys/socket.h>
#include<unistd.h>
#include<arpa/inet.h>
#include<netinet/in.h>

using namespace std;

class TcpSocket{
  public:
    TcpSocket(int fd=-1)
      :_fd(fd)
    {}
    bool Socket(){ 
      _fd=socket(AF_INET,SOCK_STREAM,0);
      if(_fd<0){
        perror("socket");
        return false;
      }
      return true;
    }
    bool Close(){
      if(_fd!=-1)
        close(_fd);
      return true;
    }
    bool Bind(const string& ip,const uint16_t port){
      sockaddr_in addr;
      addr.sin_family=AF_INET;
      addr.sin_addr.s_addr=inet_addr(ip.c_str());
      addr.sin_port=htons(port);
      int n=bind(_fd,(sockaddr*)&addr,sizeof(addr));
      if(n<0){
        perror("bind");
        return false;
      }
      return true;
    }
    //声明sockfd处于监听状态，设置等待队列大小
    bool Listen(const int log=5){
      int n=listen(_fd,log);
      if(n<0){
        perror("listen");
        return false;
      }
      return true;
    }
    //从等待队列上取一个，链接该客户端，如果没有则阻塞
    bool Accept(TcpSocket* NewSock,string& ip,uint16_t& port){
      sockaddr_in addr;
      socklen_t len=sizeof(addr);
      int newSock=accept(_fd,(sockaddr*)&addr,&len);
      if(newSock<0){
        perror("accept");
        return false;
      }
      ip=inet_ntoa(addr.sin_addr);
      port=ntohs(addr.sin_port);
      NewSock->_fd=newSock;
      return true;
    }
    //客户端调用该函数链接服务器
    bool Connect(const string& ip,const uint16_t port){
      sockaddr_in addr;
      addr.sin_family=AF_INET;
      addr.sin_addr.s_addr=inet_addr(ip.c_str());
      addr.sin_port=htons(port);
      int n=connect(_fd,(sockaddr*)&addr,sizeof(addr));
      if(n<0){
        perror("connect");
        return false;
      }
      return true;
    }
    //接收请求
    int Recv(string& msg)
    {
      char buf[1024*2]={0};
      int n=recv(_fd,buf,sizeof(buf)-1,0);
      if(n<0){
        perror("recv");
        return -1;
      }
      else if(n==0){
        return 0;
      }
      msg=buf;
      return 1;
    }
    //写回请求
    bool Send(const string& msg)
    {
      int n=send(_fd,msg.c_str(),msg.size(),0);
      if(n<0){
        perror("send");
        return false;
      }
      return true;
    }
    int GetFd()const{
      return _fd;
    }
  private:
    int _fd;
};
