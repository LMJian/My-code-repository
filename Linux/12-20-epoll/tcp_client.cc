#include"tcp_client.hpp"

int main(){
  /*TcpSocket sock;
  sock.Socket();
  sock.Connect("127.0.0.1",9090);

  while(1){
    string buf;
    cout<<"client say:";
    fflush(stdout);
    cin>>buf;
    sock.Send(buf);
    string ret;
    sock.Recv(ret);
    cout<<"ret:"<<ret<<endl;
  }*/
  TcpClient client("127.0.0.1",9090);
  client.Socket();
  client.Connect();
  //发送请求
  string buf;
  cout<<"请输入内容"<<endl;
  while(cin>>buf)
  {
    client.Send(buf);
    /*string ret;
    client.Recv(ret);
    cout<<"ret:"<<ret<<endl;
    cout<<"请输入内容"<<endl;*/
  }
  return 0;
}
