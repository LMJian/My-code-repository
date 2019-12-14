#include"tcp_socket.hpp"
#include<unistd.h>

int main()
{
  TcpSocket socket;
  socket.Bind("0.0.0.0",9090);
  socket.Listen();
  int fd=fork();
  if(fd>0){
    cout<<"子进程"<<fd<<endl;
  }
  if(fd<0)
    cout<<"进程创建失败"<<endl;

  while(1){
    sleep(1);
  }
  return 0;
}
