#pragma once
#include"tcp_socket.hpp"
#include<pthread.h>
#include"threadpool.hpp"
#include<sys/syscall.h>
#include<unistd.h>
#include<stdio.h>
  
typedef void (*Handler)(const string& ip,string& ret);
struct Arg{
  TcpSocket _sock;
  string _ip;
  int _port;
  Handler _handler;
};

class MyStack:public Stack{
  public:
    MyStack(void* arg)
      :Stack(arg)
      {}
    virtual void Entry()override
    {
      Arg *ret=(Arg*)_arg;
      TcpSocket ArgSock=ret->_sock;
      string ArgIp=ret->_ip;
      int ArgPort=ret->_port;
      Handler ArgHandler=ret->_handler;
      while(1){
        string msg;
        int n=ArgSock.Recv(msg);
        if(n<0){
          continue;
        }
        else if(n==0){
          printf("[%s:%d]客户端已经关闭！\n",ArgIp.c_str(),ArgPort);
          break;
        }
        printf("[%s:%d]客户端输入：%s\n",ArgIp.c_str(),ArgPort,msg.c_str());
        string ret;
        ArgHandler(msg,ret);
        if(ArgSock.Send(ret)==false)
          continue;
      }
      ArgSock.Close();
      delete ret;
    }
};


class TcpThreadServer{
  public:
    TcpThreadServer()
      :pool(10)
    {}
    ~TcpThreadServer(){
      _sock.Close();
    }
    bool Start(const string& ip,const int port,Handler handler){
      if(_sock.Bind(ip,port)==false)
        return false;
      if(_sock.Listen()==false)
        return false;
      while(1){
        Arg *NewArg=new Arg;
        NewArg->_handler=handler;
        if(_sock.Accept(&(NewArg->_sock),NewArg->_ip,NewArg->_port)==false)
          continue;
        printf("[%s:%d]客户端已连接！\n",NewArg->_ip.c_str(),NewArg->_port);
        pool.AddStack(new MyStack((void*)NewArg));
      }
    }

  private:
    TcpSocket _sock;
    ThreadPool pool;
};
