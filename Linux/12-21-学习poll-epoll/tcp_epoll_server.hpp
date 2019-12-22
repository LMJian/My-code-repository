#pragma once
#include"tcp_socket.hpp"
#include<sys/epoll.h>
#include<vector>
#include<iostream>
using namespace std;

#define MAXEVENTS 30

class Epoll{
  public:
    Epoll()
      :epfd_(-1)
  {}
    bool Create(){
      epfd_=epoll_create(1);
      if(epfd_<0)
        return false;
      return true;
    }
    bool Add(const TcpSocket& sock){
      int op=EPOLL_CTL_ADD;
      int fd=sock.GetFd();
      epoll_event ev;
      ev.data.fd=fd;
      ev.events=EPOLLIN|EPOLLET;
      int ret=epoll_ctl(epfd_,op,fd,&ev);
      if(ret<0)
        return false;
      return true;
    }
    bool Del(const TcpSocket& sock){
      int op=EPOLL_CTL_DEL;
      int fd=sock.GetFd();
      int ret=epoll_ctl(epfd_,op,fd,nullptr);
      if(ret<0)
        return false;
      return true;
    }
    bool Wait(vector<TcpSocket>&list,int timeout=-1){
      epoll_event evs[MAXEVENTS];
      int ret=epoll_wait(epfd_,evs,MAXEVENTS,timeout);
      if(ret<0){
        perror("epoll Wait Error ");
        return false;
      }else if(ret==0){
        cout<<"epoll wait timeout"<<endl;
        return false;
      }
      for(int i=0;i<ret;++i){
        TcpSocket sock(evs[i].data.fd);
        list.push_back(sock);
      }
      return true;
    }
    
  private:
    int epfd_;
};


typedef void (*Handler)(const string& buf,string& ret);

class TcpEpollServer{
  public:
    TcpEpollServer()
    {}
    ~TcpEpollServer(){
      _sock.Close();
    }
    bool Start(const string& ip,const uint16_t port,Handler handler){
      if(_sock.Socket()==false)
        return false;
      //_sock.SetNonBlock();//设置非阻塞
      if(_sock.Bind(ip,port)==false)
        return false;
      if(_sock.Listen()==false)
        return false;
      
      Epoll epoll;
      epoll.Create();
      epoll.Add(_sock);

      while(1){
        vector<TcpSocket> list;
        if(epoll.Wait(list)==false)
          continue;
        for(size_t i=0;i<list.size();++i){
          if(list[i].GetFd()==_sock.GetFd()){
            TcpSocket NewSock;
            string ClientIp;
            uint16_t ClientPort;
            if(_sock.Accept(&NewSock,ClientIp,ClientPort)==false)
              continue;
            printf("[%s:%d]客户端已连接！~\n",ClientIp.c_str(),ClientPort);
            //NewSock.SetNonBlock();//设置非阻塞
            epoll.Add(NewSock);
          }
          else{
            string msg;
            int n=list[i].Recv(msg);
            if(n==1){
              cout<<"客户端发送："<<msg<<endl;
              string ret;
              handler(msg,ret);
              list[i].Send(ret);
            }
            else{
              epoll.Del(list[i]);
              list[i].Close();
              continue;
            }
          }
        }
      }
      return true;
    }
  private:
    TcpSocket _sock;
};
