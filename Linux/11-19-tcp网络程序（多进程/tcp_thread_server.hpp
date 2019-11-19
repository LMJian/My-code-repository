#pragma once
#include"tcp_socket.hpp"
#include<pthread.h>
typedef void (*Handler)(const string& buf,string& ret);

class TcpThreadServer{
  public:
    TcpThreadServer(){

    }
    ~TcpThreadServer(){
      _listen_sock.Close();
    }
    bool Start(const string& ip,const int port,Handler handler){
      int n=_listen_sock.Bind(ip,port);
      if(n<0){
        return false;
      }
      n=_listen_sock.Listen();
      if(n<0){
        return false;
      }
      while(1){
        TcpSocket client_sock;
        string peer_ip;
        int peer_port;
        if(_listen_sock.Accept(&client_sock,peer_ip,peer_port)==false)
          continue;
        ProcessClient(client_sock,ip,port,handler);

      }
    }
  private:
    TcpSocket _listen_sock;
    struct ThreadEntryArg{
      TcpSocket client_sock;
      string ip;
      int port;
      Handler handler;
    };
    void ProcessClient(TcpSocket& client_sock,const string& ip,const int port,Handler handler){
      pthread_t tid;
      ThreadEntryArg* arg=new ThreadEntryArg;
      arg->client_sock=client_sock;
      arg->ip=ip;
      arg->handler=handler;
      arg->port=port;
      pthread_create(&tid,NULL,ThreadEntry,(void*)arg);
      pthread_detach(tid);
    }
    static void* ThreadEntry(void* arg){
      ThreadEntryArg* argument=(ThreadEntryArg*)arg;
      string ip=argument->ip;
      int port=argument->port;
      Handler handler=argument->handler;
      TcpSocket client_sock=argument->client_sock;

      while(1){
        string req;
        int ret=client_sock.Recv(req);
        if(ret<0){
          continue;
        }
        else if(ret==0){
          client_sock.Close();
          printf("[%s:%d]客户端断连接",ip.c_str(),port);
          break;
        }
        printf("[%s:%d]客户端断开连接\n",ip.c_str(),port);
        string resp;
        handler(req,resp);
        client_sock.Send(resp);
      }
      //delete argument;
    }
};
