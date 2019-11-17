#pragma once
#include"tcp_socket.hpp"
#include<functional>
#define CHECK_RET(exp) if(!(exp)) {\
  return false;\
}

typedef function<void(const string&,string*)> Handler;

class TcpServer{
  public:
    TcpServer(){

    }
    bool Start(const string& ip,uint16_t port,Handler handler){
      //创建socket
      CHECK_RET(listen_sock.Socket());
      //绑定端口号
      CHECK_RET(listen_sock.Bind(ip,port));
      //监听
      CHECK_RET(listen_sock.Listen());
      //进入主循环
      printf("server start~\n");
      while(1){
        //通过accept获取到一个链接
        TcpSocket client_sock;
        string ip;
        uint16_t port;
        bool ret=listen_sock.Accept(&client_sock,&ip,&port);
        if(!ret){
          continue;
        }
        printf("[%s:%d]有客户连接",ip.c_str(),port);

        //和客户端进行具体沟通，一次连接多次沟通
        while(1){
          //读取请求
          string req;
          int r=client_sock.Recv(&req);
          if(r<0){
            continue;
          }
          if(r==0){
            //对端关闭socket
            client_sock.Close();
            printf("[%s:%d]对端关闭了链接\n",ip.c_str(),port);
            break;
          }
          printf("[%s:%d]客户端发送了一句话%s\n",ip.c_str(),port,req.c_str());
          //计算响应
          string resp;
          handler(req,&resp);
          //把响应写回客户端
          client_sock.Send(resp);
      }
    }
    }
  private:
    TcpSocket listen_sock;
};
