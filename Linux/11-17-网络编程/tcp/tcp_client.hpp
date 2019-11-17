#pragma once
#include"tcp_socket.hpp"


class TcpClient{
  public:
    TcpClient(){
      sock.Socket();
    }
    ~TcpClient(){
      sock.Close();
    }
    bool Connect(const string& ip,uint16_t port){
      return sock.Connect(ip,port);
    }
    bool Recv(string* msg){
      return sock.Recv(msg);
    }
    bool Send(const string& msg){
      return sock.Send(msg);
    }

  private:
    TcpSocket sock;
};

