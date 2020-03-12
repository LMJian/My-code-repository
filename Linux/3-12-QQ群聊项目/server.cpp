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

void* startRun(void* buf){
    pthread_detach(pthread_self());
    int fd=(*(int*)buf);
    while(1){
      //阻塞等待客户端发送数据
      char buf[1024]={0};
      int rdSize=recv(fd,buf,1023,0);//阻塞
      if(rdSize<=0){
        cout<<"客户端已断开"<<endl;
        auto it=sockArr.begin();
        while(it!=sockArr.end()){
          if((*it)->_fd==fd){
            sockArr.erase(it);
            close(fd);
            break;
          }
          ++it;
        }
        break;
      }
      //给每个客户端发送服务器收到的数据，实现每个客户端数据同步
      auto it=sockArr.begin();
      while(it!=sockArr.end()){
        if((*it)->_fd!=fd){
          char str[1024]={0};
          int n=sprintf(str,"%s:%d-->%s",(*it)->_ip.c_str(),(*it)->_port,buf);
          send((*it)->_fd,str,n,MSG_DONTWAIT);//非阻塞发送
        }
        ++it;
     }
  }
  pthread_exit(NULL);
}
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

  n=listen(fd,5);
  if(n<0){
    perror("listen error");
    return 0;
  }

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
    pthread_t pid;
    n=pthread_create(&pid,NULL,startRun,&newfd);
    if(n!=0){
      perror("pthread_create error");
      return 0;
    }
  }
  close(fd);
  return 0;
}
