#include"tcp.hpp"
using namespace std;

int main(int argc,char* argv[]){
  if(argc!=3){
    cout<<"./client [ip] [port]"<<endl;
    return 0;
  }
  string ip=argv[1];
  uint16_t port=atoi(argv[2]);
  Tcp sock;
  if(!sock.Socket())
    return 0;
  struct sockaddr_in addr;
  addr.sin_family=AF_INET;
  addr.sin_port=htons(port);
  addr.sin_addr.s_addr=inet_addr(ip.c_str());

  if(!sock.Connect(&addr))
    return 0;

  while(1){
    string buf;
    Data data;
    data.a=1;
    data.b=1;

    sock.Send(&data);
    sock.Send(&data);

    sock.Recv(buf);
    cout<<"server:"<<buf<<endl;
  }
  sock.Close();
  return 0;
}
