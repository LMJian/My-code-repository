#include"tcp_client.hpp"

int main(int argc,char* argv[]){
  if(argc!=2){
    printf("Usage./dict_client [ip]\n");
    return 1;
  }
  TcpClient client;
  bool ret=client.Connect(argv[1],9090);
  if(!ret){
    printf("Connect failed!\n");
    return 1;
  }
  while(1){
   //从标准输入读数据
   printf("请输入一个要查询的单词：");
   fflush(stdout);
   char req[1024*2]={0};
   scanf("%s",req);
   //把读到的数据发送到服务器
   client.Send(req);
   string resp;
   //读取服务器的响应结果
   client.Recv(&resp);
   //吧响应结果显示到标准输出上
   printf("resp:%s\n",resp.c_str());
  }
    return 0;
}
