#include<sys/syscall.h>
#include<signal.h>
#include"tcp.hpp"
using namespace std;

void* startRun(void* buf){
    pthread_detach(pthread_self());
    Tcp* ts=(Tcp*)buf;
    while(1){
       string buf;
       int n=ts->Recv(buf);
       if(n<0){
         cout<<"recv error"<<endl;
         continue;
       }
       else if(n==0){
         cout<<"客户端已断开！"<<endl;
         break;
       }
       cout<<"client:"<<buf<<endl;
       cout<<"server:";
       fflush(stdout);
       cin>>buf;
       if(!ts->Send(buf))
         continue;
     }
     delete ts;
     pthread_exit(NULL);
}
int main(int argc,char* argv[]){
  if(argc!=3){
    cout<<"./server [ip] [port]"<<endl;
    return 0;
  }
  string ip=argv[1];
  uint16_t port=atoi(argv[2]);

  Tcp sock;
  if(!sock.Socket())
    return 0;

  if(!sock.Bind(ip,port))
    return 0;

  if(!sock.Listen(5))
    return 0;

  while(1){
    Tcp* ts=new Tcp();
    struct sockaddr_in addr;
    int n=sock.Accept(*ts,&addr);
    if(n<0)
      continue;
    cout<<"客户端"<<inet_ntoa(addr.sin_addr)<<":"<<ntohs(addr.sin_port)<<"已连接"<<endl;
    pthread_t pid;
    n=pthread_create(&pid,NULL,startRun,ts);
    if(n!=0){
      cout<<"线程创建失败"<<endl;
      return 0;
    }
  }
  return 0;
}
