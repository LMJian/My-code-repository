#include<signal.h>
#include"tcp.hpp"
#include<boost/algorithm/string.hpp>
#include<vector>
#include<stdlib.h>
#include<sstream>

using namespace std;

int Sum(string data){
  std::vector<std::string> output;
  std::string split_char="+";
  boost::split(output,data,boost::is_any_of(split_char),boost::token_compress_off);
  //int sum=atoi(output[0].c_str())+atoi(output[1].c_str());
  int sum_number=0;
  for(size_t i=0;i<output.size();++i){
    sum_number+=atoi(output[i].c_str());
  }
  return sum_number;
}

int main(int argc,char* argv[]){
  if(argc!=3){
    cout<<"./server [ip] [port]"<<endl;
    return 0;
  }
  string ip=argv[1];
  uint16_t port=atoi(argv[2]);

  signal(SIGCLD,SIG_IGN);
  Tcp sock;
  if(!sock.Socket())
    return 0;

  if(!sock.Bind(ip,port))
    return 0;

  if(!sock.Listen(5))
    return 0;
 
  while(1){
      Tcp ts;
      struct sockaddr_in addr;
      if(sock.Accept(ts,&addr)<0)
        return 0;
     
      string buf;
      ts.Recv(buf);
      cout<<"chrome send Data:"<<buf<<endl;

      //http协议去组织协议，数据格式
      //响应首行
      //响应头部
      //空行
      //正文
      //string body="<html><body><h1>hello world</h1></body></html>";
      //char arraybuf[10240]={0};
      //sprintf(arraybuf,"%s %s %s\r\nContent-Length: %lu\r\nContent-Type: %s\r\n\r\n","HTTP/1.1","200","OK",body.size(),"text/html");
      //string header;
      //header.assign(arraybuf,strlen(arraybuf));
      
      //string body="<html><body><h1>hello world</h1></body></html>";
      //stringstream ss;
      //ss<<"HTTP/1.1 200 OK\r\n";
      //ss<<"Content-Length:"<<body.size()<<"\r\n";
      //ss<<"Content-Type:text/html\r\n";
      //ss<<"\r\n";
      //string header=ss.str();

      /*string body="<html><body><h1>hello world</h1></body></html>";
      stringstream ss;
      ss<<"HTTP/1.1 302 Found\r\n";
      ss<<"Content-Length:"<<body.size()<<"\r\n";
      ss<<"Content-Type:text/html\r\n";
      ss<<"Location:https://www.baidu.com\r\n";   
      ss<<"\r\n";*/

      /*string body="<html><body><h1>hello world</h1></body></html>";
      stringstream ss;
      ss<<"HTTP/1.1 404 Page Not Found\r\n";
      ss<<"Content-Length:"<<body.size()<<"\r\n";
      ss<<"Content-Type:text/html\r\n";
      ss<<"\r\n";*/
      
      string body="<html><body><h1>hello world</h1></body></html>";
      stringstream ss;
      ss<<"HTTP/1.1 502 Bad Gateway\r\n";
      ss<<"Content-Length:"<<body.size()<<"\r\n";
      ss<<"Content-Type:text/html\r\n";
      ss<<"\r\n";
      
      string header=ss.str();
      ts.Send(header);
      ts.Send(body);
      ts.Close();
  }
  sock.Close();
  return 0;
}
