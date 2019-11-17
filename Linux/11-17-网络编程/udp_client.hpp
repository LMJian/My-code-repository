#pragma once
#include"udp_socket.hpp"

class UdpClient{
  public:
    UdpClient(const string& ip,const int port)
      :_server_ip(ip)
       ,_server_port(port)
   {
      sock.Socket();
   }
    ~UdpClient(){
      sock.Close();
    }
    bool SendTo(string& msg)
    {
        return sock.SendTo(msg,_server_ip,_server_port);
    }
    bool RecvFrom(string &msg){
        return sock.RecvFrom(msg,_server_ip,_server_port);
    }
  private:
    UdpSocket sock;
    string _server_ip;
    int _server_port;
};

