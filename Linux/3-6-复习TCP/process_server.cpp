#include<signal.h>
#include"tcp.hpp"
using namespace std;

int main(int argc,char* argv[]){
  if(argc!=3){
    cout<<"./server [ip] [port]"<<endl;
    return 0;
  }
  string ip=argv[1];
  uint16_t port=atoi(argv[2]);

  signal(SIGCLD,SIG_IGN);
  Tcp sock;
  if(!sock.Socket())
    return 0;

  if(!sock.Bind(ip,port))
    return 0;

  if(!sock.Listen(5))
    return 0;

  while(1){
    Tcp ts;
    struct sockaddr_in addr;
    int n=sock.Accept(ts,&addr);
    if(n<0)
      continue;
    cout<<"客户端"<<inet_ntoa(addr.sin_addr)<<":"<<ntohs(addr.sin_port)<<"已连接"<<endl;
    int fd=fork();
    if(fd<0){
      cout<<"进程创建失败"<<endl;
      exit(1);
    }
    else if(fd==0){
      while(1){
        string buf;
        n=ts.Recv(buf);
        if(n<0){
          cout<<"recv error"<<endl;
          continue;
        }
        else if(n==0){
          cout<<"客户端已断开！"<<endl;
          ts.Close();
          break;
        }
        cout<<"client:"<<buf<<endl;
        cout<<"server:";
        cin>>buf;
        if(!ts.Send(buf))
          continue;
      }
      ts.Close();
      exit(1);
    }
    ts.Close();
  }
  sock.Close();
  return 0;
}
