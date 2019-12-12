#include"tcp_thread_server.hpp"

void HttpProcess(const string& req,string& resp){
  (void)req;
  string first_line="HTTP/1.1 302 Found\n";
  string header="Location:http://www.sogou.com\n"
    "Content-Type:text/html\n"
    "Contect-Length:10\n";
  string body="aaaaaaaaaa";
  resp=first_line+header+"\n"+body;
}

int main(){
  TcpThreadServer server;
  server.Start("0.0.0.0",9090,HttpProcess);
  return 0;
}
