#include<iostream>
#include<unistd.h>
#include<cstdio>
#include<sys/types.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<netinet/in.h>
#include<string>

class Udp{
  public:
    Udp()
      :fd_(-1)
    {}
    ~Udp()
    {}
    bool Socket(){
      fd_=socket(AF_INET,SOCK_DGRAM,17);
      if(fd_<0){
        perror("socket error");
        return false;
      }
      return true;
    }
    bool Bind(const std::string& ip,const uint16_t& port){
      struct sockaddr_in addr;
      addr.sin_port=htons(port);
      addr.sin_family=AF_INET;
      addr.sin_addr.s_addr=inet_addr(ip.c_str());
      int ret=bind(fd_,(struct sockaddr*)&addr,sizeof(addr));
      if(ret<0){
        perror("bind error");
        return false;
      }
      return true;
    }
    //接收数据
    bool RecvFrom(std::string& buf,struct sockaddr_in* addr){
      char chBuf[1024]={0};
      socklen_t addrlen=sizeof(*addr);
      int ret=recvfrom(fd_,chBuf,sizeof(chBuf)-1,0,(struct sockaddr*)addr,&addrlen);
      if(ret<0){
        perror("recvfrom error");
        return false;
      } 
      buf=chBuf;
      return true;
    }
    //发送数据
    bool SendTo(const std::string& buf,const struct sockaddr_in* addr){
      socklen_t addrlen=sizeof(*addr);
      int ret=sendto(fd_,buf.c_str(),buf.size(),0,(struct sockaddr*)addr,addrlen);
      if(ret<0){
        perror("sendto error");
        return false;
      }
      return true;
    }
    void Close(){
      close(fd_);
      fd_=-1;
    }
  private:
    int fd_;
};

