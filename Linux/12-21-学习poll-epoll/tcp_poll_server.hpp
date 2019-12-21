#pragma once
#include"tcp_socket.hpp"
#include<poll.h>
#include<unistd.h>
#include<cstring>
#include<vector>

class Poll{
  public:
    Poll()
      :fds_(nullptr)
       ,fds_size_(15)
       ,nfds_(0)
       ,timeout_(1000)
  {
    fds_=new pollfd[fds_size_];
  }
    bool Add(const TcpSocket& sock){
      if(nfds_==fds_size_){//需要扩容
        pollfd *new_fds=new pollfd[2*fds_size_];
        memcpy(new_fds,fds_,fds_size_*sizeof(pollfd));
        fds_size_*=2;
        delete[] fds_;
        fds_=new_fds;
      }
      fds_[nfds_].fd=sock.GetFd();
      fds_[nfds_].events=POLLIN;
      ++nfds_;
      return true;
    }
    bool Del(const TcpSocket& sock){
      int del_fd=sock.GetFd();
      for(size_t i=0;i<nfds_;++i){
        if(fds_[i].fd==del_fd){
          fds_[i]=fds_[--nfds_];
          break;
        }
      }
      return true;
    }
    bool Wait(vector<TcpSocket>&list,int timeout=1000){
      timeout_=timeout;
      int ret=poll(fds_,nfds_,timeout_);
      if(ret<0){
        perror("Poll Wait");
        return false;
      }else if(ret==0){
        cout<<"poll wait timeout"<<endl;
        return false;
      }
      for(nfds_t i=0;i<nfds_;++i){
        if(fds_[i].revents==POLLIN){
          TcpSocket sock(fds_[i].fd);
          list.push_back(sock);
        }
      }
      return true;
    }
    int GetNfds(){
      return nfds_;
    }
    const pollfd* GetFds(){
      return fds_;
    }
  private:
    pollfd *fds_;
    nfds_t fds_size_;
    nfds_t nfds_;
    int timeout_;
};


typedef void (*Handler)(const string& buf,string& ret);

class TcpPollServer{
  public:
    TcpPollServer()
    {}
    ~TcpPollServer(){
      _sock.Close();
    }
    bool Start(const string& ip,const uint16_t port,Handler handler){
      if(_sock.Socket()==false)
        return false;
      if(_sock.Bind(ip,port)==false)
        return false;
      if(_sock.Listen()==false)
        return false;
      
      Poll poll;
      poll.Add(_sock);

      while(1){
        vector<TcpSocket> list;
        if(poll.Wait(list)==false)
          continue;
        for(size_t i=0;i<list.size();++i){
          if(list[i].GetFd()==_sock.GetFd()){
            TcpSocket NewSock;
            string ClientIp;
            uint16_t ClientPort;
            if(_sock.Accept(&NewSock,ClientIp,ClientPort)==false)
              continue;
            printf("[%s:%d]客户端已连接！~\n",ClientIp.c_str(),ClientPort);
            poll.Add(NewSock);
          }
          else{
            string msg;
            int n=list[i].Recv(msg);
            if(n==0){
              poll.Del(list[i]);
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
