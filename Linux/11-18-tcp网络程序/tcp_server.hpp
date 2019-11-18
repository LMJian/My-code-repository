#pragma once
#include"tcp_socket.hpp"


//服务器一启动就要绑定ip和port

typedef void (*Handler)(const string& buf,string& ret);

class TcpServer{
  public:
    TcpServer(const string& ip,const int port)
      :_ip(ip)
       ,_port(port)
    {}
    ~TcpServer(){
      _sock.Close();
    }
    bool Start(Handler hand){
      if(_sock.Bind(_ip,_port)==false)
        return false;
      if(_sock.Listen()==false)
        return false;
      cout<<"server start ok~"<<endl;
      while(1){
        TcpSocket newSock;
        //从等待队列里链接一个客户端
        //此处传_ip和_port,复用了
        int n=_sock.Accept(&newSock,_ip,_port);
        if(n<0){
          continue;
        }
        printf("客户端[%s:%d]已连接\n",_ip.c_str(),_port);
        while(1){
          //读取请求
          string msg;
          n=newSock.Recv(msg);
          if(n<0){
            printf("recv error\n");
            continue;
          }
          else if(n==0){
            printf("客户端已断开！\n");
            newSock.Close();
            break;
          }
          cout<<"用户输入了："<<msg<<endl;
          //处理请求
          string ret;
          hand(msg,ret);
          printf("[%s:%d]msg:%s ret:%s\n",_ip.c_str(),_port,msg.c_str(),ret.c_str());
          //写回请求
          n=newSock.Send(ret);
          if(n<0){
            continue;
          }
        }
      } 
    }
  private:
    TcpSocket _sock;
    string _ip;
    int _port;
};


