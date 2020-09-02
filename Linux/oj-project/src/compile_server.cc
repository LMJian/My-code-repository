#include<unordered_map>
#include "httplib.h"
#include "compile.hpp"
#include <jsoncpp/json/json.h>

int main(){
    using namespace httplib;
    Server server;

    server.Post("/compile",[](const Request& req,Response& resp){
        (void)req;
        //如果从req获取到json请求，json如何和http协议结合
        //需要的请求格式是json格式，而http能够提供的格式，
        //是另外一种键值对的格式，所以此处要进行格式的转换
        //此处由于提交的代码可能会包含一些特殊符号，这些特殊符号要想正确传输，就
        //需要进行转义，浏览器自动帮我们完成了。
        //然后解析这个数据整理成需要的json格式
        //键值对，用哪个数据结构来表示？
        std::unordered_map<std::string,std::string> body_kv;
        UrlUtil::ParseBody(req.body,&body_kv);
        //在这里调用CompileAndRun函数
        Json::Value req_json;    //从req获取
        for(auto p : body_kv){
            req_json[p.first] = p.second;
        }
        Json::Value resp_json;   //放到响应中
        Compiler::CompileAndRun(req_json,&resp_json);
        //需要把json对象序列化成一个字符串，才能返回
        Json::FastWriter writer;
        resp.set_content(writer.write(resp_json),"text/plain");
    });
    //加上这个目录是为了让浏览器能够访问到一个静态页面
    //静态页面：index.html
    //动态页面：编译结果 随着参数的不同而发生变化
    server.set_base_dir("./wwwroot");
    server.listen("0.0.0.0",9092);
    
    return 0;
}