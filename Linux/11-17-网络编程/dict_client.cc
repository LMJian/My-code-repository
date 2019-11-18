#include"udp_client.hpp"


int main(){
  UdpClient client("127.0.0.1",9090);
  string msg;
  cout<<"请输入内容"<<endl;
  while(cin>>msg)
  {
    client.SendTo(msg);
    string ret;
    client.RecvFrom(ret);
    cout<<ret<<endl;

  cout<<"请输入内容"<<endl;
  }
     return 0;
}
