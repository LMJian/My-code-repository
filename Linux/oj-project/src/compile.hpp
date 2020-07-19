#pragma once
#include<string>
//此代码完成在线编译模块的功能
//提供一个Compiler类，由这个类提供一个核心的CompileAndRun类
//由这个函数来完成编译+运行的功能

class Compiler{
public:
  //此处参数格式为json
  static bool CompileAndRun(const std::string& req_json,
                            std::string* resp_json){
    
  }
};