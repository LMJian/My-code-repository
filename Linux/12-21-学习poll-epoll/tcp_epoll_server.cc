#include"tcp_epoll_server.hpp"

void test(const string& msg,string& ret){
  auto it=msg.begin();
  while(it!=msg.end()){
    if(*it>='a'&&*it<='z'){
      ret.push_back(*it-32);
    }
    else{
      ret.push_back(*it+32);
    }
    ++it;
  }
}
int main(){
  TcpEpollServer server;
  server.Start("0.0.0.0",9090,test);
  return 0;
}
