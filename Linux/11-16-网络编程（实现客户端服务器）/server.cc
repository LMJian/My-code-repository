#include<unistd.h>
#include<iostream>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>//sockaddr_in所在头文件
#include<arpa/inet.h>//inet_addr所在头文件
#include<stdio.h>
using namespace std;

int main()
{
  int sock=socket(AF_INET,SOCK_DGRAM,0);
  if(sock<0){
    perror("socket");
    return 1;
  }

  //服务器绑定该端口号
  sockaddr_in addr;
  addr.sin_family=AF_INET;
  addr.sin_addr.s_addr=inet_addr("0.0.0.0");
  addr.sin_port=htons(9090);
  socklen_t len=sizeof(addr);
  int n=bind(sock,(sockaddr*)&addr,len);
  if(n<0){
    perror("bind");
    return 1;
  }
  printf("server start~~\n");

  char buf[1024]={0};
  //客户端数据
  sockaddr_in src_addr;
  len=sizeof(src_addr);
  while(1){
    fflush(stdout);
    //读取
    n=recvfrom(sock,&buf,sizeof(buf)-1,0,(sockaddr*)&src_addr,&len);
    if(n<0){
      perror("recvfrom");
      continue;
    }
    //写回
    n=sendto(sock,&buf,sizeof(buf),0,(sockaddr*)&src_addr,len);
    if(n<0){
      perror("sendto");
      continue;
    }
    printf("[%s:%d]:%s\n",inet_ntoa(src_addr.sin_addr),ntohs(src_addr.sin_port),buf);
  }
  return 0;
}
