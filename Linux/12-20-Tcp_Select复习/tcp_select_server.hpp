#pragma once
#include"tcp_socket.hpp"
#include<signal.h>
#include<sys/select.h>
#include<sys/time.h>
#include<sys/types.h>
#include<unistd.h>
#include<vector>

class Select{
  public:
    Select()
      :max_nfds_(-1)
    {
      FD_ZERO(&readfds);
    }
    bool Add(const TcpSocket& sock){
      FD_SET(sock.GetFd(),&readfds);
      if(sock.GetFd()>max_nfds_)
        max_nfds_=sock.GetFd();
      return true;
    }
    bool Del(const TcpSocket& sock){
      FD_CLR(sock.GetFd(),&readfds);
      for(int i=max_nfds_;i>=0;--i){
        if(FD_ISSET(i,&readfds)){
          max_nfds_=i;
          break;
        }
      }
      return true;
    }
    bool Wait(vector<TcpSocket>& list){
      fd_set set=readfds;
      int n=select(max_nfds_+1,&set,NULL,NULL,NULL);
      if(n<0){
        perror("select");
        return false;
      }
      else if(n==0){
        cout<<"select wait timeout!"<<endl;
        return false;
      }
      else{
        for(int i=0;i<=max_nfds_;++i){
          if(FD_ISSET(i,&set)){
            TcpSocket sock(i);
            list.push_back(sock);
          }
        }
        return true;
      }
    }
  private:
    int max_nfds_;
    fd_set readfds;
};


typedef void (*Handler)(const string& buf,string& ret);

class TcpSelectServer{
  public:
    TcpSelectServer()
    {}
    ~TcpSelectServer(){
      _sock.Close();
    }
    bool Start(const string& ip,const uint16_t port,Handler handler){
      if(_sock.Socket()==false)
        return false;
      if(_sock.Bind(ip,port)==false)
        return false;
      if(_sock.Listen()==false)
        return false;
      
      Select select;
      select.Add(_sock);

      while(1){
        vector<TcpSocket> list;
        if(select.Wait(list)==false)
          continue;
        int size=list.size();
        for(int i=0;i<size;++i){
          if(list[i].GetFd()==_sock.GetFd()){
            TcpSocket NewSock;
            string ClientIp;
            uint16_t ClientPort;
            if(_sock.Accept(&NewSock,ClientIp,ClientPort)==false)
              continue;
            printf("[%s:%d]客户端已连接！~\n",ClientIp.c_str(),ClientPort);
            select.Add(NewSock);
          }
          else{
            string msg;
            int n=list[i].Recv(msg);
            if(n==0){
              select.Del(list[i]);
              list[i].Close();
              continue;
            }else{
              cout<<"客户端发送："<<msg<<endl;
              string ret;
              handler(msg,ret);
              list[i].Send(ret);
            }
          }
        }
      }
      return true;
    }
  private:
    TcpSocket _sock;
};
