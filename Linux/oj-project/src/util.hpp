#pragma once
#include<cstdlib>
#include<stdint.h>
#include<string>
#include<iostream>
#include<sys/time.h>
#include<fstream>

//准备一个获取时间戳的工具
class TimeUtil{
    public:

    static int64_t TimeStamp(){
        struct timeval tv;
        ::gettimeofday(&tv,NULL);
        return tv.tv_sec;
    }

    static int64_t TimeStampMS(){
        struct timeval tv;
        ::gettimeofday(&tv,NULL);
        return tv.tv_sec*1000+tv.tv_usec/1000;
    }
};

//打印日志的工具
//期望打印出的日志格式 如：
//[I1595144574] util.hpp:31]hello
//[W1595144574] util.hpp:31]hello
//[E1595144574] util.hpp:31]hello
//[F1595144574] util.hpp:31]hello
//日志的使用方式 如：
//LOG(INFO) << "hello" << "\n";
//日志的级别：
//FATAL 致命
//ERROR 错误
//WARNING 警告
//INFO 提示

enum Level{
    INFO,
    WARNING,
    ERROR,
    FATAL,
};

inline std::ostream& Log(Level level,
                        const std::string& file_name,
                        int line_num){
    std::string prefix = "[";
    if(level == INFO){
        prefix+="I";
    }
    else if(level==WARNING){
        prefix+="W";
    }
    else if(level==ERROR){
        prefix+="E";
    }
    else if(level==FATAL){
        prefix+="F";
    }
    prefix += std::to_string(TimeUtil::TimeStamp());
    prefix += " ";
    prefix += file_name;
    prefix += ";";
    prefix += std::to_string(line_num);
    prefix += "]";
    std::cout<<prefix;
    return std::cout;
}

#define LOG(level) Log(level,__FILE__,__LINE__)

//准备文件相关的工具
class FileUtil{
    public:
    //指定一个文件路径，帮我们把文件的所有内容都读进来放到content字符串中
    static bool Read(const std::string& file_path,
                    std::string* content){
        content->clear();
        std::ifstream file(file_path.c_str());
        if(!file.is_open()){
            return false;
        }
        std::string line;
        while(std::getline(file,line)){
            *content+=line+'\n';
        }
        file.close();
        return true;
    }
    static bool Write(const std::string& file_path,
                    const std::string& content){
        std::ofstream file(file_path.c_str());
        if(!file.is_open()){
            return false;
        }
        file.write(content.c_str(),content.size());
        file.close();
        return true;
    }
};
