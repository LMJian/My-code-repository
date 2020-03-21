#pragma once
#include<iostream>
#include<vector>
#include<boost/algorithm/string.hpp>

//实现一个切割字符串
class StringTools{
  public:
    static void Split(const std::string& input,const std::string& split_char,std::vector<std::string>* output){
      boost::split(*output,input,boost::is_any_of(split_char),boost::token_compress_off);
    }
};
