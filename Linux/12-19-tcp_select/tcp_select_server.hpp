#pragma once
#include<sys/select.h>
#include<iostream>
#include<vector>
#include <set>
#include"tcp_socket.hpp"

//用一个线程来实现TCP服务器


bool operator<(const TcpSocket& lsh,const TcpSocket& rsh)
{
    return lsh.GetFd()<rsh.GetFd();
}

//主要要实现的功能：
//1.新增一个文件描述符
//2.删除一个文件描述符
//3.等待操作（等待管理文件描述符的就绪）
class Selector
{
    public:
        void Add(const TcpSocket& sock)
        {
            printf("[select:Add]%d\n",sock.GetFd());
            socket_set.insert(sock);

        }

        //Wait返回时要告诉调用者哪些文件描述符就绪了
        void Wait(vector<TcpSocket>* output)
        {
            output->clear();
            //调用select进行等待

            //先获取最大文件描述符+1
            if(socket_set.empty())
            {
                printf("[selector::wait],socket_set is empty"); 
                return ;
            }
            int max_fd=socket_set.rbegin()->GetFd();

            //设置读就绪
            fd_set readfds;

            FD_ZERO(&readfds);//初始化

            //把set中每个需要关注的文件描述符都设置到readfds中
            for(const auto& sock:socket_set)
            {
                FD_SET(sock.GetFd(),&readfds);
            }

            //select默认是阻塞式等待，有文件描述符返回时，才进行返回,当函数返回后，根据文件描述符的情况
            //构造一个输出型参数，告诉调用者哪些描述符socket就绪了
            int nfds=select(max_fd+1,&readfds,NULL,NULL,NULL);
            if(nfds<0)
            {
                perror("select");
                return ;
            }

            //已经返回了，返回结果同样保存在readfds中
            for(int fd=0;fd<max_fd+1;fd++)
            {
                //判断描述是否在readfds中，如果在，就说明时读就绪
                if(FD_ISSET(fd,&readfds))
                    //把结果放到输出结果中
                    output->push_back(TcpSocket(fd));
            }
        }

        void Del(const TcpSocket& sock)
        {
            printf("[select:del]%d\n",sock.GetFd());
            socket_set.erase(sock);
        }
    private:
        //得用一个数据结构存储需要的socket
        //1.需要高效的插入删除  2.方便找到最大元素--->>用set
        set<TcpSocket> socket_set;
};

//实现select版本的tcp server


#include<functional>
typedef function<void(const string&,string*)>Handler;
#define CHECK_RET(exp)\
    if(!(exp)){\
        return false;\
    }

class TcpSelectServer
{
    public:
        //1.读取用户请求并解析
        //2.根据请求计算相应(handler)
        //3.把响应写回客户端
        bool Start(const string& ip,uint16_t port,Handler handler)
        {
            //1.创建socket
            TcpSocket listen_sock;
            bool ret = listen_sock.Socket();
            CHECK_RET(ret);

            //2.绑定端口号
            CHECK_RET(listen_sock.Bind(ip,port));

            //3.监听文件描述符
            CHECK_RET(listen_sock.Listen());

            //4.创建一个select对象,让这个对象把listen_sock管理起来,后续的等待都是靠selector来完成
            Selector selector;
            selector.Add(listen_sock);

            //5.进入主循环
            while(1)
            {
                //6.不再调用accept,而是使用selector进行等待
                vector<TcpSocket>out;

                //wait操作同时等待多个文件描述符
                selector.Wait(&out);

                //7.遍历返回结果，以此处理每个就绪的socket文件描述符
                for(auto tcp_socket:out)
                {
                    //8.分成两种情况：
                    //    a).如果就绪socket是listen_socket就调用accept
                    //    b).如果就绪的socket不是listen_socket就调用recv

                    if(tcp_socket.GetFd()==listen_sock.GetFd())
                    {
                        string ip;
                        uint16_t port;
                        TcpSocket client_sock;
                        tcp_socket.Accept(&client_sock,&ip,&port);
                        selector.Add(client_sock);
                        printf("[client %s:%d] connected!\n",ip.c_str(),port);
                    }
                    else
                    {
                        string req;
                        int n = tcp_socket.Recv(&req);
                        if(n<0)
                        {
                            continue;
                        }
                        else if(n==0)
                        {
                            printf("对端关闭");
                            //如果对端关闭，本端也要关闭，还要把该socket从selector中删除调
                            tcp_socket.Close();
                            selector.Del(tcp_socket);
                            continue;
                        }
                        printf("[client] %s:\n",req.c_str());
                        //计算响应
                        string resp;
                        handler(req,&resp);

                        //给客户端返回结果
                        tcp_socket.Send(resp);

                    }


                }
            }

        }
    private:
};
