//#include"tcp_server.hpp"
#include"tcp_select_server.hpp"
#include<unordered_map>

int main()
{
    TcpSelectServer server;
    unordered_map<string,string>dict;
    dict.insert(make_pair("hello","你好"));
    dict.insert(make_pair("wolf ","爱你"));
    dict.insert(make_pair("guidao","哟"));
    dict.insert(make_pair("bite","比特"));
    dict.insert(make_pair("world","世界"));
    dict.insert(make_pair("feiwu","废物"));
    server.Start("0.0.0.0",9090,[&dict](const string& req,string* resp){
            auto it = dict.find(req);
            if(it==dict.end())
            {
            *resp="未找到";
            }
            else
            {
            *resp=it->second;
            }
            });
    return 0;
}
