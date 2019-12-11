#include"tcp_thread_server.hpp"

void HttpProcess(const string& req,string& resp){
  (void)req;
  string first_line="HTTP/1.1 200 OK\n";
  string body="<html><div>hello world</div></html>";
  string header="Content-Type:test/html\nContent-Length:"+to_string(body.size())+"\n";
  resp=first_line+body+header;
}

int main(){
  TcpThreadServer server;
  server.Start("0.0.0.0",9090,HttpProcess);
  return 0;
}
