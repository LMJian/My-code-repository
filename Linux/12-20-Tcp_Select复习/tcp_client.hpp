#pragma once
#include"tcp_socket.hpp"

//客户端
class TcpClient{
  public:
    TcpClient(const string& ip,const uint16_t port)
      :_server_ip(ip)
       ,_server_port(port)
  {
    if(_sock.Connect(_server_ip,_server_port)==false)
      perror("Connect");
  }
    ~TcpClient(){
      _sock.Close();
    }
    bool Send(const string& msg){
      return _sock.Send(msg);
    }
    bool Recv(string& ret){
      return _sock.Recv(ret);
    }
  private:
    TcpSocket _sock;
    string _server_ip;
    uint16_t _server_port;
};
