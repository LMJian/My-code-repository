#pragma once
#include<stdio.h>
#include<cstring>
#include<unistd.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<string>

class UdpSocket{
private:
  UdpSocket()
    :_fd(-1)
  {}
  bool Socket()
  {
    _fd=socket(AF_INET,SOCK_DGRAM,0);
    if(_fd<0)
    {
      perror("socket");
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
  bool Bind(const std::string& ip,const int port)
  {
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
  bool RecvFrom(std::string& msg,std::string& ip,int& port)
  {
    char buf[1024*2]={0};
    sockaddr_in addr;
    socklen_t len=sizeof(addr);
    int n=recvfrom(_fd,&buf,sizeof(buf)-1,0,(sockaddr*)&addr,&len);
    if(n<0){
      perror("recvfrom");
      return false;
    }
    msg=buf;
    ip=inet_ntoa(addr.sin_addr);
    port=ntohs(addr.sin_port);
    return true;
  }
  bool SendTo(const std::string& msg,const std::string& ip,int port)
  {
    sockaddr_in addr;
    addr.sin_family=AF_INET;
    addr.sin_addr.s_addr=inet_addr(ip.c_str());
    addr.sin_port=htons(port);
    int n=sendto(_fd,msg.c_str(),msg.size(),0,(sockaddr*)&addr,sizeof(addr));
    if(n<0){
      perror("bendto");
      return false;
    }
    return true;
  }
private:
  int _fd;
};
