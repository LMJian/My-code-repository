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
      int fd=fork();
      if(fd==0){
        cout<<"子进程："<<getpid()<<endl;
        //return false;
      }
      if(fd>0){
        cout<<"父进程："<<getpid()<<endl;
        return false;
      }
      while(1){
        TcpSocket client_sock;
        string peer_ip;
        int peer_port;
        if(_listen_sock.Accept(&client_sock,peer_ip,peer_port)==false)
          continue;
        printf("[%s:%d]客户端已连接！\n",peer_ip.c_str(),peer_port);
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
          printf("[%s:%d]客户端断连接!\n",ip.c_str(),port);
          break;
        }
        printf("[%s:%d]客户端输入:%s\n",ip.c_str(),port,req.c_str());
        string resp;
        handler(req,resp);
        client_sock.Send(resp);
      }
      client_sock.Close();
      delete argument;
      return NULL;
    }
};
