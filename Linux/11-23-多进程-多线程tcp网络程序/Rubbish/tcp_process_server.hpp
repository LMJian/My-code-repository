#pragma once
#include"tcp_socket.hpp"
#include<signal.h>

typedef void (*Handler)(const string& buf,string& ret);

class TcpProcessServer{
  public:
    TcpProcessServer()
    {}
    ~TcpProcessServer(){
      _listen_sock.Close();
    }
    bool Start(const string& ip,const int port,Handler handler){
      signal(SIGCLD,SIG_IGN);
      int n=_listen_sock.Bind(ip,port);
      if(n<0){
        perror("Bind");
        return false;
      }
      n=_listen_sock.Listen();
      if(n<0){
        perror("listen");
        return false;
      }
      while(1){
        TcpSocket client_sock;
        string peer_ip;
        int peer_port;
        if(_listen_sock.Accept(&client_sock,peer_ip,peer_port)==false)
          continue;
        printf("[%s:%d]客户端建立连接！\n",peer_ip.c_str(),peer_port);
        ProcessConnect(client_sock,peer_ip,peer_port,handler);
      }
    }

  private:
    TcpSocket _listen_sock;
    void ProcessConnect(TcpSocket& client_sock,const string& ip,const int port,Handler handler){
      pid_t ret=fork();
      if(ret>0)
      {
        client_sock.Close();
        return;
      }
      while(1){
        string req;
        int r=client_sock.Recv(req);
        if(r<0){
          continue;
        }
        else if(r==0){
          printf("[%s:%d]客户端断开连接！\n",ip.c_str(),port);
          break;
        }
        printf("[%s:%d]客户端发送了%s\n",ip.c_str(),port,req.c_str());

        string resp;
        handler(req,resp);
        client_sock.Send(resp);
      }
      client_sock.Close();
      exit(0);
    }
};

