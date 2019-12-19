#include"tcp_client.hpp"
#include<signal.h>
#define CHECK_RET(ret)\
  if(!(req)){\
    perror("CHECK_RET");\
  }

void sigcb(int signo){
  (void)signo;
  printf("connection closed\n");
}

int main(int argc,char *argv[]){
  if(argc!=3){
    cout<<"./tcp_cli 192.168.122.132 9090\n";
    return -1;
  }
  string ip=argv[1];
  int port=atoi(argv[2]);
  signal(SIGPIPE,sigcb);

  TcpSocket sock;
  sock.Socket();
  sock.Connect(ip,port);

  while(1)
  {
    string buf;
    cout<<"client say:";
    fflush(stdout);
    cin>>buf;
    sock.Send(buf);
    cout<<"server say:"<<buf<<endl;
  }
  return 0;
}
