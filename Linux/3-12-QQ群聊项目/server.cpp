#include<sys/syscall.h>
#include<signal.h>
#include<list>
#include<iostream>    
#include<unistd.h>
#include<cstdio>
#include<sys/types.h>
#include<sys/socket.h>
#include<arpa/inet.h>          
#include<netinet/in.h>     
#include<string> 
#include"threadpool.cpp"

using namespace std;

list<struct cliMessage*> sockArr;

struct cliMessage{
  cliMessage(int fd,char* ip,uint16_t port)
    :_fd(fd)
     ,_ip(ip)
     ,_port(port)
  {}
  int _fd;
  string _ip;
  uint16_t _port;
};

class MyStart:public Start{
  public:
    MyStart(int fd,char* ip,uint16_t port)
      :_fd(fd)
       ,_ip(ip)
       ,_port(port)
    {}
    virtual void Run()override{
      while(1){
        //阻塞等待客户端发送数据
        char buf[1024]={0};
        int rdSize=recv(_fd,buf,1023,0);//阻塞
        if(rdSize<=0){
          cout<<"客户端已断开"<<endl;
          auto it=sockArr.begin();
          while(it!=sockArr.end()){
            if((*it)->_fd==_fd){
              sockArr.erase(it);
              close(_fd);
              break;
            }
            ++it;
          }
          break;
        }
        //给每个客户端发送服务器收到的数据，实现每个客户端数据同步
        auto it=sockArr.begin();
        while(it!=sockArr.end()){
          if((*it)->_fd!=_fd){
            char str[1024]={0};
            int n=sprintf(str,"%s:%d-->%s",_ip.c_str(),_port,buf);
            send((*it)->_fd,str,n,MSG_DONTWAIT);//非阻塞发送
          }
          ++it;
      }
    }
  }
  private:
    int _fd;
    string _ip;
    uint16_t _port;
};


int main(int argc,char* argv[]){
  if(argc!=3){
    cout<<"./server [ip] [port]"<<endl;
    return 0;
  }
  string ip=argv[1];
  uint16_t port=atoi(argv[2]);

  int fd=socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
  if(fd<0){
    perror("socket error");
    return 0;
  }

  struct sockaddr_in addr;
  addr.sin_addr.s_addr=inet_addr(ip.c_str());
  addr.sin_port=htons(port);
  addr.sin_family=AF_INET;
  int n=bind(fd,(struct sockaddr*)&addr,sizeof(addr));
  if(n<0){
    perror("bind error");
    return 0;
  }

  n=listen(fd,10);
  if(n<0){
    perror("listen error");
    return 0;
  }

  //创建线程池
  ThreadPool pool(3);

  while(1){
    struct sockaddr_in addr;
    socklen_t addrlen=sizeof(addr);
    int newfd;
    newfd=accept(fd,(struct sockaddr*)&addr,&addrlen);
    if(newfd<0){
      perror("accept error");
      continue;
    }
    cout<<"客户端"<<inet_ntoa(addr.sin_addr)<<":"<<ntohs(addr.sin_port)<<"已连接"<<endl;
    sockArr.push_back(new cliMessage(newfd,inet_ntoa(addr.sin_addr),ntohs(addr.sin_port)));  //将已经链接的sock插入链表
    
    MyStart* start=new MyStart(newfd,inet_ntoa(addr.sin_addr),ntohs(addr.sin_port));
    pool.push(start);
  }
  close(fd);
  return 0;
}
