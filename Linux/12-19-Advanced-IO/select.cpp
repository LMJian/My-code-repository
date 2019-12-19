#include"tcp_socket.hpp"
#include<vector>
#include<sys/select.h>
#include<sys/time.h>
#include<sys/types.h>
#include<unistd.h>

class Select{
  public:
    Select()
      :_max_fd(-1){
      FD_ZERO(&_rfds);
    }
    bool Add(const TcpSocket& sock){
      int fd=sock.GetFd();
      FD_SET(fd,&_rfds);
      _max_fd=_max_fd>fd?_max_fd:fd;
      return true;
    }
    bool Del(const TcpSocket& sock){
      int fd=sock.GetFd();
      FD_CLR(fd,&_rfds);
      for(int i=_max_fd;i>=0;--i){
        if(FD_ISSET(i,&_rfds)){
          _max_fd=i;
          break;
        }
      }
      return true;
    }
    bool Wait(vector<TcpSocket>& list,int timeout_sec=3){
      struct timeval tv;
      tv.tv_sec=timeout_sec;
      tv.tv_usec=0;
      fd_set set=_rfds;
      int ret=select(_max_fd+1,&set,NULL,NULL,&tv);
      if(ret<0){
        perror("select error");
        return false;
      }else if(ret==0){
        cout<<"select wait timeout\n";
        return false;
      }
      for(int i=0;i<=_max_fd;++i){
        if(FD_ISSET(i,&set)){
          TcpSocket sock(i);
          list.push_back(sock);
        }
      }
      return true;
    }
private:
    fd_set _rfds;
    int _max_fd;
};

#define CHECK_RET(ret)\
  if(!(ret)){\
    perror("CHECK_RET");\
  }

int main(){
  TcpSocket sock;
  CHECK_RET(sock.Socket());
  CHECK_RET(sock.Bind("0.0.0.0",9090));
  CHECK_RET(sock.Listen());

  Select s;
  s.Add(sock);
  while(1){
    vector<TcpSocket> list;
    if(s.Wait(list)==false)
      continue;
    for(int i=0;i<list.size();++i){
      if(list[i].GetFd()==sock.GetFd()){
        TcpSocket cli_sock;
        string cli_ip;
        int cli_port;
        if(sock.Accept(&cli_sock,cli_ip,cli_port)==false)
          continue;
        s.Add(cli_sock);
      }else{
        string buf;
        if(list[i].Recv(buf)==false){
          s.Del(list[i]);
          list[i].Close();
          continue;
        }
        cout<<"client say:"<<buf<<"\n";
      } 
    }
  }
  return 0;
}
