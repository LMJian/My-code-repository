#pragma once
#include"tcp_socket.hpp"
#include<signal.h>

typedef void (*Handler)(const string& buf,string& ret);

class TcpProcessServer{
  public:
    TcpProcessServer()
    {}
    ~TcpProcessServer(){
      _sock.Close();
    }
    bool Start(const string& ip,const int port,Handler handler){
      signal(SIGCLD,SIG_IGN);
      if(_sock.Bind(ip,port)==false)
        return false;
      if(_sock.Listen()==false)
        return false;
      while(1){
        TcpSocket NewSock;
        string ClientIp;
        int ClientPort;
        if(_sock.Accept(&NewSock,ClientIp,ClientPort)==false)
          continue;
        printf("[%s:%d]客户端已连接！~\n",ClientIp.c_str(),ClientPort);
        ProcessConnect(NewSock,ClientIp,ClientPort,handler);
      }
      return true;
    }
  private:
    void ProcessConnect(TcpSocket& NewSock,const string& ip,const int port,Handler handler){
      int fid=fork();
      if(fid>0){
        NewSock.Close();
        return;
      }
      while(1){
        string msg;
        int n=NewSock.Recv(msg);
        if(n<0){
          continue;
        }
        else if(n==0){
          printf("[%s:%d]客户端已断开！\n",ip.c_str(),port);
          break;
        }
        printf("[%s:%d]客户端发送了:%s\n",ip.c_str(),port,msg.c_str());
        string ret;
        handler(msg,ret);
        if(NewSock.Send(ret)==false)
          continue;
      }
      NewSock.Close();
      exit(0);
    }
    TcpSocket _sock;
};
