#include<stdio.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<cstring>
#include<unistd.h>

int main(int argc,char* argv[])
{
  int sock=socket(AF_INET,SOCK_DGRAM,0);
  if(sock<0){
    perror("socket");
    return 1;
  }

  sockaddr_in server_addr;
  server_addr.sin_family=AF_INET;
  server_addr.sin_addr.s_addr=inet_addr(argv[1]);
  server_addr.sin_port=htons(9090);


  while(1)
  {
    char buf[1024]={0};
    printf("请输入一段内容：");
    fflush(stdout);
    scanf("%s",buf);
    sendto(sock,buf,strlen(buf),0,(sockaddr*)&server_addr,sizeof(server_addr));
    char buf_output[1024]={0};
    recvfrom(sock,buf_output,sizeof(buf_output)-1,0,NULL,NULL);
    printf("server resp:%s\n",buf_output);
  }


  return 0;
}
