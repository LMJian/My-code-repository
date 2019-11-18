#include"tcp_server.hpp"

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
int main(int argc,char* argv[]){
  if(argc<2)
  {
    perror("main");
    return 1;
  }
  TcpServer server(argv[1],9090);
  server.Start(test);
  return 0;
}
