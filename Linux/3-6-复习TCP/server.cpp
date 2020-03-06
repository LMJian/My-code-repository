#include"tcp.hpp"
using namespace std;

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
    Tcp ts;
    struct sockaddr_in addr;
    int n=sock.Accept(ts,&addr);
    if(n<0)
      continue;
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
  }
  sock.Close();
  return 0;
}
