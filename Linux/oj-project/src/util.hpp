//所用到的工具类

#pragma once
#include<iostream>
#include<string>
#include<vector>
#include<unordered_map>
#include<sys/time.h>
#include<fstream>
#include<boost/algorithm/string.hpp>

//切分oj_config.cfg文件中的每行字符串
class StringUtil{
public:
    static void Split(const std::string& input,
                      const std::string& split_char,
                      std::vector<std::string>* output){

        boost::split(*output,input,boost::is_any_of(split_char),
                    boost::token_compress_on);
    }
};

//文件读写工具
class FileUtil{
public:
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

//解析body， 获取用户提交的代码
class UrlUtil{
public:
    static void ParseBody(const std::string& body,
                          std::unordered_map<std::string,std::string>* params){
        //对body字符串进行切分，切分成键值对的形式
        //       a)按照 & 切分
        std::vector<std::string> kvs;
        StringUtil::Split(body,"&",&kvs);

        //       b)再按照 = 切分
        for(size_t i=0;i<kvs.size();++i){
            std::vector<std::string> kv;
            //kvs[i]里面存放的是一个键值对
            StringUtil::Split(kvs[i],"=",&kv);
            if(kv.size()!=2){
                continue;
            }
            //对value进行UrlDecode
            (*params)[kv[0]] = UrlDecode(kv[1]);
        }
    }

    static std::string UrlDecode(const std::string& str){
        std::string strTemp = "";
        size_t length = str.length();
        for (size_t i = 0; i < length; i++)
        {
            if (str[i] == '+') strTemp += ' ';
            else if (str[i] == '%')
            {
                assert(i + 2 < length);
                unsigned char high = FromHex((unsigned char)str[++i]);
                unsigned char low = FromHex((unsigned char)str[++i]);
                strTemp += high*16 + low;
            }
            else strTemp += str[i];
        }
        return strTemp;
    }
 
    static unsigned char FromHex(unsigned char x) 
    { 
        unsigned char y;
        if (x >= 'A' && x <= 'Z') y = x - 'A' + 10;
        else if (x >= 'a' && x <= 'z') y = x - 'a' + 10;
        else if (x >= '0' && x <= '9') y = x - '0';
        else assert(0);
        return y;
    }
};

//获取时间戳的工具
class TimeUtil{
public:
    static int64_t TimeStamp(){
        struct timeval tv;
        ::gettimeofday(&tv,NULL);
        return tv.tv_sec;
    }
};

//打印日志的工具
//期望打印出的日志格式 如：[I1595144574 util.hpp:31]hello

#define LOG(level) Log(level,__FILE__,__LINE__)

enum Level{
    INFO,      //提示
    WARNING,   //警告
    ERROR,     //错误
    FATAL,     //致命
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