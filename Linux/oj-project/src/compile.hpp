#pragma once
#include<string>
#include<atomic>
#include<unistd.h>
#include<sys/wait.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<jsoncpp/json/json.h>
#include"util.hpp"
//此代码完成在线编译模块的功能
//提供一个Compiler类，由这个类提供一个核心的CompileAndRun类
//由这个函数来完成编译+运行的功能


class Compiler{
public:
  //此处参数格式为json
  //Json::Value类jsoncpp中的核心类，借助这个类就可以完成序列化和反序列化
  
  //本质上使用文件完成进程间通信
  //1.源代码文件,name表示当前请求的名字
  // 请求和请求之间，name必须是不相同的 
  static std::string SrcPath(const std::string& name){
    return "./temp_files/"+name+".cpp";
  }
  //2.编译错误文件
  static std::string CompileErrorPath(const std::string& name){
    return "./temp_files/"+name+".compile_error";
  }
  //3.可执行程序文件
  static std::string ExePath(const std::string& name){
    return "./temp_files/"+name+".exe";
  }
  //4.标准输入文件
  static std::string StdinPath(const std::string name){
    return "./temp_files/"+name+".stdin";
  }
  //5.标准输出文件
  static std::string StdoutPath(const std::string name){
    return "./temp_files/"+name+".stdout";
  }
  //6.标准错误文件
  static std::string StderrPath(const std::string name){
    return "./temp_files/"+name+".stderr";
  }
  static bool CompileAndRun(const Json::Value& req,
                            Json::Value* resp){
    //1.根据请求对象，生成源代码文件,和标准输入文件
    if(req["code"].empty()){
      (*resp)["error"]=3;
      (*resp)["reason"]="code empty";
      LOG(ERROR)<<"code empty"<<std::endl;
      return false;
    }
    //req["code"]根据key取出value， value类型也是
    //Json::value,这个类型通过asString()转成字符串
    const std::string& code = req["code"].asString();
    //通过这个函数完成把代码写到代码文件中的过程
    std::string file_name = WriteTmpFile(code,req["stdin"].asString());
    
    //2.调用g++进行编译（fork + exec）
    //    生成可执行程序，如果编译出错，需要把编译错误记录下来（重定向到文件中）
    bool ret = Compile(file_name);
    if(!ret){
      //错误处理
      (*resp)["error"]=1;
      std::string reason;
      FileUtil::Read(CompileErrorPath(file_name),&reason);
      (*resp)["reason"]=reason;
      //虽然是编译出错，但是是用户自己的错误，不是服务器的
      LOG(INFO)<<"Compile failed!"<<std;:endl;
      return false;
    }
    //3.调用可执行程序，把标准输入记录到文件中，然后把文件中的内容重定向给可执行程序，
    // 可执行程序的标准输出和标准错误内容也要重定向输出记录到文件中
    int sig = Run(file_name);
    if(sig!=0){
      //错误处理
      (*resp)["error"]=2;
      (*resp)["reason"] = "Program exit by signo: "+std::to_string(sig);
      LOG(INFO)<<"Program exit by signo: "<<std::to_string(sig)<<std::endl;
      return false;
    }
    //4.把程序的最终结果进行返回，构造resp对象
    (*resp)["error"] = 0;
    (*resp)["reason"] = "";
    std::string str_stdout;
    FileUtil::Read(StdoutPath(file_name),&str_stdout);
    (*resp)["stdout"]=str_stdout;
    std::string str_stderr;
    FileUtil::Read(StderrPath(file_name),&str_stderr);
    (*resp)["stderr"] = str_stderr;
    LOG(INFO) << "Program " << file_name << " Done" << std::endl;
    return true;
  }

private:
  //1.把代码写到文件中
  //2.给这次请求分配一个唯一的名字，通过返回值返回
  //    如：tmp_1595144574.2
  static std::string WriteTmpFile(const std::string& code,const std::string& str_stdin){
    //原子操作依赖cpu的支持
    static std::atomic_int id(0);
    ++id;
    std::string file_name = "tmp_"
                            +std::to_string(TimeUtil::TimeStamp())
                            +"."
                            +std::to_string(id);
    FileUtil::Write(SrcPath(file_name),code);

    FileUtil::Write(StdinPath(file_name),str_stdin);

    return file_name;
  }

  static bool Compile(const std::string& file_name){
    //1.先构造出编译指令
    //  g++ file_name.cpp -o file_name.exe -std=c++11
    char* command[20] = {0};
    char buf[20][50]={{0}};
    for(int i=0;i<20;++i){
      command[i]=buf[i];
    }
    //必须要保证command的指针都是指向有效内存
    sprintf(command[0],"%s","g++");
    sprintf(command[1],"%s",SrcPath(file_name).c_str());
    sprintf(command[2],"%s","-o");
    sprintf(command[3],"%s",ExePath(file_name).c_str());
    sprintf(command[4],"%s","-std=c++11");
    command[5]=NULL;
    //2.创建子进程
    int ret = fork();
    //3.父进程进行进程等待
    if(ret>0){
      waitpid(ret,NULL,0);
    }
    //4.子进程进行进程替换
    else{
      int fd = open(CompileErrorPath(file_name).c_str(),O_WRONLY|O_CREAT,0666);
      if(fd<0){
        LOG(ERROR)<< "open Compile file error" <<std::endl;
        exit(1);
      }
      dup2(fd,2);  //期望标准输出的结果输入到文件中
      execvp(command[0],command);
      //子进程替换错误的话就直接退出
      exit(0);
    }
    //5. 代码执行到这里，如何知道编译成功与否？
    //判定可执行文件是否存在，stat
    struct stat st;
    ret= stat(ExePath(file_name).c_str(),&st);
    if(ret<0){
      //stat执行失败 文件不存在
      LOG(INFO)<<"Compile failed! "<< file_name <<std::endl;
      return false;
    }
    LOG(INFO)<<"Compile "<<file_name<<"OK!"<<std::endl;
    return ture;
  }

  static int Run(const std::string& file_name){
    //1. 创建子进程
    int ret = fork();
    //2. 父进程等待
    if(ret>0){
      int status=0;
      waitpid(ret,&status,0);
      return status & 0x7F;
    }
    else{
      //3. 进行重定向
      int fd_stdin = open(StdinPath(file_name).c_str(),
                          O_RDONLY);
      dup2(fd_stdin,0);
      int fd_stdout = open(StdoutPath(file_name).c_str(),
                          O_WRONLY|O_CREAT,0666);
      dup2(fd_stdout,1);
      int fd_stderr = open(StderrPath(file_name).c_str(),
                          O_WRONLY|O_CREAT,0666);
      dup2(fd_stderr,2);
      //4. 子进程程序替换
      execl(ExePath(file_name).c_str(),
            ExePath(file_name).c_str(),
            NULL);
      exit(0);
    }
    
  }
};