#include<jsoncpp/json/json.h>
#include"util.hpp"
#include"compile.hpp"

int main(){
    Json::Value req;
    req["code"]="#include<stdio.h> \n int main(){ printf(\"hehe\"); return 0;}";
    req["stdin"] = "";
    Json::Value resp;
    Compiler::CompileAndRun(req,&resp);
    Json::FastWriter writer;
    LOG(INFO) << writer.write(resp) << std::endl;

    return 0;
}