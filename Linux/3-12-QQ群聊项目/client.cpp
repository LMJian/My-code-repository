#include<fcntl.h>
#include<iostream>          
#include<unistd.h>
#include<cstdio>
#include<sys/types.h>
#include<sys/socket.h>
#include<arpa/inet.h>          
#include<netinet/in.h>     
#include<string> 
#include<cstring>

using namespace std;

int main(int argc,char* argv[]){
  if(argc!=3){
    cout<<"./client [ip] [port]"<<endl;
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
  addr.sin_family=AF_INET;
  addr.sin_port=htons(port);
  addr.sin_addr.s_addr=inet_addr(ip.c_str());
  int n=connect(fd,(struct sockaddr*)&addr,sizeof(addr));
  if(n<0){
    perror("connect error");
    return 0;
  }
  //将stdout设置为非阻塞
  if(fcntl(0,F_SETFL,FNDELAY)<0){
    perror("fcntl");
    return 0;
  }
  while(1){
    char buf[1024]={0};
    n=read(0,buf,1023);
    if(n>0){
      send(fd,buf,n,MSG_DONTWAIT);//非阻塞发送
    }
    memset(buf,0,1024);
    n=recv(fd,buf,1023,MSG_DONTWAIT);
    if(n>0){
      printf("%s",buf);
    }
  }
  close(fd);
  return 0;
}
