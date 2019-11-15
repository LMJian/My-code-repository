#include<stdio.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<cstring>
#include<unistd.h>


int main()
{
  int sock=socket(AF_INET,SOCK_DGRAM,0);
  if(sock<0){
    perror("socket");
    return 1;
  }
  sockaddr_in addr;
  addr.sin_family=AF_INET;
  addr.sin_addr.s_addr=inet_addr("0.0.0.0");
  addr.sin_port=htons(9090);
  int ret=bind(sock,(sockaddr*)&addr,sizeof(addr));
  if(ret<0)
  {
    perror("bind");
    return 1;
  }
  printf("server start ok!\n");
  while(true){
    char buf[1024]={0};
    sockaddr_in peer;
    socklen_t len=sizeof(peer);
    ssize_t n=recvfrom(sock,buf,sizeof(buf)-1,0,(sockaddr*)&peer,&len);
    if(n<0){
      perror("recvfrom");
      continue;
    }
    buf[n]='\0';


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
