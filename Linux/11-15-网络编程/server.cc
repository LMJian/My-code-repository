#include<stdio.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<cstring>
#include<unistd.h>


int main()
{
  //1.
  int sock=socket(AF_INET,SOCK_DGRAM,0);
  //AF_INET表示IPv4地址类型
  //SOCK_DGRAM表示使用UDP协议
  if(sock<0){
    perror("socket");
    return 1;
  }
  //2.绑定IP+端口号
  sockaddr_in addr;//IPv4编程使用该结构
  addr.sin_family=AF_INET;//表示IPv4
  addr.sin_addr.s_addr=inet_addr("0.0.0.0");//绑定端口号,该函数自动转为网络字节序
  addr.sin_port=htons(9090);//将端口号转为网络字节序
  int ret=bind(sock,(sockaddr*)&addr,sizeof(addr));
  if(ret<0)
  {
    perror("bind");
    return 1;
  }
  printf("server start ok!\n");
  
  //3.处理请求（读取，响应，写回）
  while(true){
    //a.读取
    char buf[1024]={0};//保存读取的数据
    sockaddr_in peer;//客户端ip+端口
    socklen_t len=sizeof(peer);//输入输出型参数
    //面向数据报的函数接口
    ssize_t n=recvfrom(sock,buf,sizeof(buf)-1,0,(sockaddr*)&peer,&len);
    if(n<0){
      perror("recvfrom");
      continue;
    }
    buf[n]='\0';
    //b.响应
    //c.写回
    n=sendto(sock,buf,strlen(buf),0,(sockaddr*)&peer,len);
    if(n<0)
    {
      perror("sendto");
      continue;
    }
    printf("[%s:%d]buf:%s\n",inet_ntoa(peer.sin_addr),ntohs(peer.sin_port),buf);
  }
  close(sock);
  return 0;
}
