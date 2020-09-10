//在线编译模块    编译+运行
#pragma once
#include<string>
#include<atomic>
#include<unistd.h>
#include<sys/wait.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<jsoncpp/json/json.h>
#include"util.hpp"

class Compiler{
public:
  //1.源代码文件   (用户提交代码+测试用例代码)
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
  static std::string StdinPath(const std::string& name){
    return "./temp_files/"+name+".stdin";
  }
  //5.标准输出文件
  static std::string StdoutPath(const std::string& name){
    return "./temp_files/"+name+".stdout";
  }
  //6.标准错误文件
  static std::string StderrPath(const std::string& name){
    return "./temp_files/"+name+".stderr";
  }

  //编译并运行
  static bool CompileAndRun(const Json::Value& req,
                            Json::Value* resp){
    //1.根据请求对象，生成源代码文件和标准输入文件
    if(req["code"].empty()){
      (*resp)["error"]=3;
      (*resp)["reason"]="code empty";
      LOG(ERROR)<<"code empty"<<std::endl;
      return false;
    }
    const std::string& code = req["code"].asString();
    
    //2. 将源代码和标准输入写入文件
    const std::string& file_name = WriteTmpFile(code,req["stdin"].asString());
    
    //3. 调用Compile编译生成可执行程序，如果编译错误要写入文件。 
    bool ret = Compile(file_name);
    if(!ret){
      (*resp)["error"]=1;
      //读取编译错误原因
      std::string reason;
      FileUtil::Read(CompileErrorPath(file_name),&reason);
      (*resp)["reason"]=reason;
      LOG(INFO)<<"Compile failed!"<<std::endl;
      return false;
    }
    //3.调用可执行程序
    int sig = Run(file_name);
    if(sig!=0){
      (*resp)["error"]=2;
      //读取运行错误原因
      std::string reason;
      FileUtil::Read(StderrPath(file_name),&reason);
      (*resp)["reason"] = reason;
      LOG(INFO)<<"Program exit by signo: "<<std::to_string(sig)<<std::endl;
      return false;
    }
    //4.把程序的最终结果进行返回，构造resp对象
    (*resp)["error"] = 0;
    (*resp)["reason"] = "";
    std::string str_stdout;
    FileUtil::Read(StdoutPath(file_name),&str_stdout);
    (*resp)["stdout"]=str_stdout;
    LOG(INFO) << "Program " << file_name << " Done" << std::endl;
    return true;
  }

private:
  static std::string WriteTmpFile(const std::string& code,const std::string& str_stdin){
    static std::atomic_int id(0);
    ++id;

    //1.给这次请求分配一个唯一的名字，通过返回值返回
    std::string file_name = "tmp_"
                            +std::to_string(TimeUtil::TimeStamp())
                            +"."
                            +std::to_string(id);

    //2.将源代码和标准输入写入文件
    FileUtil::Write(SrcPath(file_name),code);
    FileUtil::Write(StdinPath(file_name),str_stdin);

    return file_name;
  }

  static bool Compile(const std::string& file_name){
    //1. 构造编译指令   g++ file_name.cpp -o file_name.exe -std=c++11
    char* command[10] = {0};
    char buf[10][50]={{0}};
    for(int i=0;i<10;++i){
      command[i]=buf[i];
    }
    sprintf(command[0],"%s","g++");
    sprintf(command[1],"%s",SrcPath(file_name).c_str());
    sprintf(command[2],"%s","-o");
    sprintf(command[3],"%s",ExePath(file_name).c_str());
    sprintf(command[4],"%s","-std=c++11");
    command[5]=NULL;

    //2.创建子进程
    int ret = fork();
    if(ret>0){

      //3.父进程进行进程等待
      waitpid(ret,NULL,0);
    }

    //4.子进程进行进程替换
    else{
      int fd = open(CompileErrorPath(file_name).c_str(),O_WRONLY|O_CREAT,0666);
      if(fd<0){
        LOG(ERROR)<< "open CompileError file error" <<std::endl;
        exit(1);
      }
      //重定向到标准输出
      dup2(fd,2);
      //进程替换
      execvp(command[0],command);
      exit(0);
    }

    //5. 可执行文件的存在与否即可判断是否编译成功
    struct stat st;
    ret= stat(ExePath(file_name).c_str(),&st);
    if(ret<0){
      //文件不存在
      LOG(INFO)<<"Compile failed! "<< file_name <<std::endl;
      return false;
    }
    LOG(INFO)<<"Compile "<<file_name<<" OK!"<<std::endl;
    return true;
  }

  static int Run(const std::string& file_name){
    //1. 创建子进程
    int ret = fork();
    if(ret>0){
      int status=0;
      //2. 父进程进程等待
      waitpid(ret,&status,0);
      return status & 0x7F;
    }
    else{
      //3. 进行重定向
      int fd_stdout = open(StdoutPath(file_name).c_str(),
                           O_WRONLY|O_CREAT,0666);
      dup2(fd_stdout,1);
      int fd_stderr = open(StderrPath(file_name).c_str(),
                           O_WRONLY|O_CREAT,0666);
      dup2(fd_stderr,2);

      //4. 程序替换
      execl(ExePath(file_name).c_str(),
            ExePath(file_name).c_str(),
            NULL);
      exit(0);
    }
  }
};