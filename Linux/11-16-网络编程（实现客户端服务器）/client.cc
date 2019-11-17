#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<iostream>
#include<arpa/inet.h>

using namespace std;

int main(int argc,char* argv[])
{
  int sock=socket(AF_INET,SOCK_DGRAM,0);
  if(sock<0){
    perror("sock");
    return 1;
  }
  //客户端不需要绑定

  char buf[1024]={0};
  //服务器信息
  sockaddr_in addr;
  addr.sin_family=AF_INET;
  addr.sin_port=htons(9090);
  addr.sin_addr.s_addr=inet_addr(argv[1]);
  
  while(1){
    printf("请输入内容：");
    scanf("%s",buf);
    //请求服务器
    int n=sendto(sock,&buf,sizeof(buf),0,(sockaddr*)&addr,sizeof(addr));
    if(n<0){
      perror("sendto");
      continue;
    }
    //读取服务器返回的数据，这里不需要知道服务器信息，后两个参数置空
    n=recvfrom(sock,&buf,sizeof(buf)-1,0,NULL,NULL);
    if(n<0){
      perror("revcfrom");
      continue;
    }
    printf("server return :%s\n",buf);
  }
  return 0;
}
