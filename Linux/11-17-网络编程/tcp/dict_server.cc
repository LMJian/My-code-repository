#include<unordered_map>
#include"tcp_server.hpp"


int main(){
  unordered_map<string,string>dict;
  dict.insert(make_pair("hello","你好"));
  dict.insert(make_pair("world","世界"));
  dict.insert(make_pair("man","男人"));

  TcpServer server;
  server.Start("0.0.0.0",9090,[&dict](const string& req,string* resp){
      auto it=dict.find(req);
      if(it==dict.end()){
        *resp="未找到结果";
      }
      else{
        *resp=it->second;
      }
    });
  return 0;
}
