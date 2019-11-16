#include<stdio.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<cstring>
#include<unistd.h>

int main(int argc,char* argv[])
{
  //1.创建sock
  int sock=socket(AF_INET,SOCK_DGRAM,0);//AF_INET表示ipv4地址类型
                                        //SOCK_DGRAM表示使用udp协议
  if(sock<0){
    perror("socket");
    return 1;
  }
  //客户端一般不需要bind
  //bind意味着和某个具体的端口号关联在一起
  //没有bind,操作系统随机分配端口号
  //服务器必须bind，因为要固定端口号，否则客户端无法链接
  //客户端如果自己bind,可能你绑定了一个重复的端口号会出现问题
  
  //2.准备服务器的信息
  sockaddr_in server_addr;
  server_addr.sin_family=AF_INET;
  server_addr.sin_addr.s_addr=inet_addr(argv[1]);
  server_addr.sin_port=htons(9090);

  //3.客户端发送数据
  while(1)
  {
    char buf[1024]={0};
    printf("请输入一段内容：");
    fflush(stdout);
    scanf("%s",buf);
    sendto(sock,buf,strlen(buf),0,(sockaddr*)&server_addr,sizeof(server_addr));
    //接收返回结果
    char buf_output[1024]={0};
    //后面两个参数NULL,表示不关注对端地址
    recvfrom(sock,buf_output,sizeof(buf_output)-1,0,NULL,NULL);
    printf("server resp:%s\n",buf_output);
  }

  return 0;
}
