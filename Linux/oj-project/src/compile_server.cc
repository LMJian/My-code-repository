#include "httplib.h"
#include "compile.hpp"
#include <jsoncpp/json/json.h>

int main(){
    using namespace httplib;
    Server server;

    server.Get("/compile",[](const Request& req,Response& resp){
        (void)req;
        //如果从req获取到json请求，json如何和http协议结合
        //json如何进行解析和构造？ 使用jsoncpp

        //在这里调用CompileAndRun函数
        Json::Value req_json;    //从req获取
        Json::Value resp_json;   //放到响应中
        Compiler::CompileAndRun(req_json,&resp_json);
        //需要把json对象序列化成一个字符串，才能返回
        Json::FastWriter writer;
        resp.set_content(writer.write(resp_json),"text/plain");
    });

    server.listen("0.0.0.0",9092);

    return 0;

}