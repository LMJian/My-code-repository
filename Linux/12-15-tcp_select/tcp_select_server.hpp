#pragma once
#include"tcp_socket.hpp"
#include<vector>
#include<set>
#include<sys/select.h>


bool operator<(const TcpSocket& lhs,const TcpSocket& rhs){
  return lhs.GetFd()<rhs.GetFd();
}
class Selector{
  public:
    void Add(const TcpSocket& sock){
      printf("[Selector::Add]%d\n",sock.GetFd());
      _socket_set.insert(sock);
    }
    void Del(const TcpSocket& sock){
      printf("[Selector::Add]%d\n",sock.GetFd());
      _socket_set.erase(sock);
    }
    //wait返回的时间需要告诉调用者哪些文件描述符就绪了
    void Wait(vector<TcpSocket>* output){
      //调用wait就相当于调用select进行等待
      //先获取最大文件描述符
      if(_socket_set.empty()){
        printf("[Selector::Wait]_socket_set is empty\n");
        return;
      }
      int max_fd=_socket_set.rbegin()->GetFd();
      fd_set readfds;
      FD_ZERO(&readfds);
      //把set中的每一个需要关注的文件描述符都设置到readfds中
      for(auto sock:_socket_set){
        FD_SET(sock.GetFd(),&readfds);
      }
      //select默认是阻塞等待，有文件描述符返回的时候，才会进行返回
      //当这个函数返回之后，就应该根据文件描述符的返回情况
      //构造一个输出参数，告诉调用者哪些socket就绪了
      int nfds=select(max_fd+1,&readfds,NULL,NULL,NULL);
      if(nfds<0){
        perror("select");
        return;
      }
      //返回结果同样是保存在readfds中
      for(int fd=0;fd<max_fd+1;++fd){
        if(FD_ISSET(fd,&readfds)){
          //如果是，说明当前fd就是读就绪的
          //就把这个结果放到输出结果中
          output->push_back(TcpSocket(fd));
        }
      }

    }
  private:
    //得用一个数据结构把需要的socket存起来
    //要求TCpSocket类能支持比较操作（operator<)
    set<TcpSocket> _socket_set;
};

//实现一个select版本的Tcp server
typedef void Handler(const string&,string&);

#define CHECK_RET(exp)\
  if(!exp){\
    return false;\
  }

class TcpSelectServer{
  public:
    //一个服务器程序就是三个步骤
    //1.读取请求
    //2.根据请求计算响应
    //3.把响应写回客户端
    bool Start(const string& ip,uint16_t port,Handler handler){
      //1.创建socket
      TcpSocket listen_sock;
      //2.绑定端口号
      CHECK_RET(listen_sock.Bind(ip,port));
      //3.监听文件描述符
      CHECK_RET(listen_sock.Listen());
      //4.先创建一个selecter对象，先把listen sock管理起来
      //后须进行等待，都是靠selector对象完成
      Selector selector;
      selector.Add(listen_sock);
      //5.进入主循环
      while(1){ 
        //6.不再是直接调用accept，而是使用selector进行等待
        vector<TcpSocket> output;
        selector.Wait(&output);
        //7.遍历返回结果，依次处理每个就绪的socket
        for(auto tcp_socket:output){
            //8.分成两种情况讨论
            //a)如果就绪的socket是listen_sock要进行的操作是调用accept
          if(tcp_socket.GetFd()==listen_sock.GetFd()){
            TcpSocket client_sock;
            string ip;
            int port;
            tcp_socket.Accept(&client_sock,ip,port);
            selector.Add(client_sock);
            printf("[client %s:%d]connected!\n",ip.c_str(),port);
          }
          else{
            //b)如果就绪的socket不是listen_sock要进行的操作是调用recv
            string req;
            int n=tcp_socket.Recv(req);
            if(n<0){
              continue;
            }
            else if(n==0){
              //对端关闭,也要把这个socket从selector中删除
              tcp_socket.Close();
              selector.Del(tcp_socket);
              continue;
            }
            printf("[client] %s\n",req.c_str());
            string resp;
            //根据请求计算响应
            handler(req,resp);
            tcp_socket.Send(resp);
          }
            
        }
      }

    }
};
