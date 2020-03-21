#include<iostream>
#include<unistd.h>
#include<cstdio>
#include<sys/types.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<netinet/in.h>
#include<string>
#include<string.h>

typedef struct Data{
  int a;
  int b;
}DATA;


class Tcp{
  public:
    Tcp()
      :fd_(-1)
    {}
    ~Tcp()
    {
      Close();
    }
    bool Socket(){
      fd_=socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
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
    bool Listen(int n){
      int ret=listen(fd_,n);
      if(ret<0){
        perror("listen error");
        return false;
      }
      return true;
    }
    //请求链接
    bool Connect(const struct sockaddr_in* addr){
      socklen_t addrlen=sizeof(*addr);
      int ret=connect(fd_,(const struct sockaddr*)addr,addrlen);
      if(ret<0){
        perror("connect error");
        return false;
      }
      return true;
    }
    //获取客户端的连接
    int Accept(Tcp& ts,struct sockaddr_in* addr){
      socklen_t addrlen=sizeof(*addr);
      int ret=accept(fd_,(struct sockaddr*)addr,&addrlen);
      if(ret<0){
        perror("accept error");
        return -1;
      }
      ts.fd_=ret;
      return 1;
    } 
    //接收数据
    int Recv(std::string& buf){
      char chBuf[1024]={0};
      int ret=recv(fd_,chBuf,sizeof(chBuf)-1,0);
      if(ret<0){
        perror("recv error");
        return -1;
      }
      else if(ret==0){
        return 0;
      }
      buf=chBuf;
      return 1;
    }
    int Recv(Data& data){
      char buf[sizeof(DATA)+1]={0};
      int ret=recv(fd_,buf,sizeof(Data),0);
      if(ret<0){
        perror("recv error");
        return -1;
      }
      else if(ret==0){
        return 0;
      }
      memcpy(&data,buf,sizeof(DATA));
      return 1;
    }
    //发送数据
    bool Send(const std::string& buf){
      int ret=send(fd_,buf.c_str(),buf.size(),0);
      if(ret<0){
        perror("send error");
        return false;
      }
      return true;
    }
    bool Send(Data* data){
      int ret=send(fd_,data,sizeof(DATA),0);
      if(ret<0){
        perror("send error");
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

