#include"udp.hpp"
using namespace std;

int main(int argc,char* argv[]){
  if(argc!=3){
    cout<<"./server [ip] [port]"<<endl;
    return 0;
  }
  string ip=argv[1];
  uint16_t port=atoi(argv[2]);
  Udp sock;

  if(!sock.Socket())
    return 0;

  if(!sock.Bind(ip,port))
    return 0;

  while(1){
    string buf;
    struct sockaddr_in addr;
    if(!sock.RecvFrom(buf,&addr))
      return 0;
    cout<<"client:"<<buf<<endl;
    cout<<"server:";
    cin>>buf;
    if(!sock.SendTo(buf,&addr))
      return 0;
  }
  sock.Close();
  return 0;
}
