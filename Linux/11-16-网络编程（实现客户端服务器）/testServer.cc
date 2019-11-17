#include"udp_server.hpp"

void testServer(string& msg){
  msg="么么哒"+msg;
}
int main(){
  UdpServer server;
  server.Start("0.0.0.0",9090,testServer);
  return 0;
}
