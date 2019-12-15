#include"tcp_client.hpp"

int main(int argc,char *argv[]){
  if(argc<2){
    perror("main");
    return 1;
  }
  TcpClient client(argv[1],9090);
  //发送请求
  string buf;
  cout<<"请输入内容"<<endl;
  while(cin>>buf)
  {
    client.Send(buf);
    string ret;
    client.Recv(ret);
    cout<<"ret:"<<ret<<endl;
    cout<<"请输入内容"<<endl;
  }

  return 0;
}
