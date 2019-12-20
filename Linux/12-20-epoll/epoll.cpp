#include<iostream>
#include<vector>
#include<sys/epoll.h>
#include"tcp_socket.hpp"

#define MAX_EVENTS 10

class Epoll{
  public:
    bool Init(){
      _epfd=epoll_create(1);
      if(_epfd<0){
        cerr<<"Init error"<<endl;
        return false;
      }
      return true;
    }
    bool Add(const TcpSocket& sock){
      int fd=sock.GetFd();
      struct epoll_event ev;
      ev.data.fd=fd;
      ev.events=EPOLLIN|EPOLLET;
      int ret=epoll_ctl(_epfd,EPOLL_CTL_ADD,fd,&ev);
      if(ret<0){
        return false;
      }
      return true;
    }
    bool Del(const TcpSocket& sock){
      int fd=sock.GetFd();
      int ret=epoll_ctl(_epfd,EPOLL_CTL_DEL,fd,NULL);
      if(ret<0){
        return false;
      }
      return true;
    }
    bool Wait(vector<TcpSocket>& list,int timeout_msec=3000){
      struct epoll_event evs[MAX_EVENTS];
      int nfds=epoll_wait(_epfd,evs,MAX_EVENTS,timeout_msec);
      if(nfds<0){
        cerr<<"epoll wait error"<<endl;
        return false;
      }else if(nfds==0){
        cerr<<"epoll wait timeout"<<endl;
        return false;
      }
      for(int i=0;i<nfds;++i){
        TcpSocket sock(evs[i].data.fd);
        list.push_back(sock);
      }
      return true; 
    }
  private:
    int _epfd;
};

int main(){
  TcpSocket listen_sock;
  listen_sock.Socket();
  listen_sock.Bind("0.0.0.0",9090);
  listen_sock.Listen();
  
  Epoll epoll;
  epoll.Init();
  epoll.Add(listen_sock);


  while(1){
    vector<TcpSocket> list;
    bool ret=epoll.Wait(list);
    if(ret==false){
      continue;
    }
    for(size_t i=0;i<list.size();++i){
      if(listen_sock.GetFd()==list[i].GetFd()){
        TcpSocket cli_sock;
        string cli_ip;
        uint16_t cli_port;
        bool ret=listen_sock.Accept(&cli_sock,cli_ip,cli_port);
        if(ret==false){
          continue;
        }
        epoll.Add(cli_sock);
      }else{
        string buf;
        bool ret=list[i].Recv(buf);
        if(ret==false){
          epoll.Del(list[i]);
          list[i].Close();
          continue;
        }
        cout<<"client:say:"<<buf<<endl;
      }
    }
  }
  listen_sock.Close();
  return 0;
}
