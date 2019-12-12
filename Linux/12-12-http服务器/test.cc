#include"tcp_socket.hpp"

int main(){
  TcpSocket sock1;
  sock1.Bind("0.0.0.0",9090);
  sock1.Listen();
  fork();
  while(1){
    sleep(1);
  }

  return 0;
}
