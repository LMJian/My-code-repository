#pragma once
#include"udp_socket.hpp"
#include<functional>

//typedef void (*Handler)(string& buf);
typedef function<void(const string&,string*)>Handler;

class UdpServer{
  public:
    UdpServer()
    {}
    ~UdpServer(){
      sock.Close();
    }
    bool Start(const string& ip,const int port,Handler hand){
      if(sock.Socket()==false)
        return false;
      if(sock.Bind(ip,port)==false)
        return false;
      printf("server start~\n");
      while(1){
        string buf;
        string peer_ip;
        int peer_port;
        if(sock.RecvFrom(buf,peer_ip,peer_port)==false)
          continue;
        string resp;
        //hand(buf);
        hand(buf,&resp);
        if(sock.SendTo(buf,peer_ip,peer_port)==false)
          continue;
        printf("[%s:%d]buf:%s,resp:%s\n",peer_ip.c_str(),peer_port,buf.c_str(),resp.c_str());
      }
    }
  private:
    UdpSocket sock;
};
