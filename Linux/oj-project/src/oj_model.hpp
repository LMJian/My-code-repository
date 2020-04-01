#pragma once
#include<iostream>
#include<string>
#include<unordered_map>
#include<vector>
#include<fstream>
#include<algorithm>

#include"tools.hpp"
#include"oj_log.hpp"

//试题id 试题名称 试题路径 试题难度
typedef struct Question{
  std::string id_;
  std::string name_;
  std::string path_;
  std::string star_;
}QUES;

class OjModel{
  public:
    OjModel(){
      LoadQuetions("./config_oj.cfg");
    }
    bool GetAllQuestions(std::vector<Question>* ques){
      for(const auto& kv:model_map_){
        ques->push_back(kv.second);
      }

      //arr[10]
      //sort(arr,arr+5)
      //sort(arr,arr+10,func)
      //针对内置类型进行操作的
      //std::greater降序排序
      //std::less升序进行排序
      std::sort(ques->begin(),ques->end(),[](const Question& l,const Question& r){
          return std::atoi(l.id_.c_str())<std::atoi(r.id_.c_str());
          });
      return true;
    }

    bool GetOneQuestion(const std::string& id,std::string* desc,std::string* header,Question* ques){
      //1. 根据id去查找对应的题目信息，最重要的是这个题目在哪加载
      auto iter=model_map_.find(id);
      if(iter==model_map_.end()){
        LOG(ERROR,"Not Found Question id is")<<id<<std::endl;
        return false;
      }
      //iter->second.path_+ 文件名称（dect.txt header.cpp)
      *ques=iter->second;

      //加载具体的单个题目信息，从保存的路径上面去加载
      //从具体的题目文件当中去获取两部分信息，描述，header头
      int ret=FileOper::ReadDataFromFile(DescPath(iter->second.path_),desc);
      if(ret==-1){
        LOG(ERROR,"Read desc failed")<<std::endl;
        return false;
      }

      ret=FileOper::ReadDataFromFile(HeaderPath(iter->second.path_),header);
      if(ret==-1){
        LOG(ERROR,"Read desc failed")<<std::endl;
        return false;
      }
      return true;
    }

  private:
    bool LoadQuetions(const std::string& configfile_path){
      std::ifstream file(configfile_path.c_str());
      if(!file.is_open()){
        return false;
      }

      std::string line;
      while(std::getline(file,line)){
        //1 单链表 ./xxx 难度
        //1、需要切割字符串
        std::vector<std::string> vec;
        StringTools::Split(line," ",&vec);
        if(vec.size()!=4){
          continue;
        }
        //2、切割后的内容保存到unordered_map
        Question ques;
        ques.id_=vec[0];
        ques.name_=vec[1];
        ques.path_=vec[2];
        ques.star_=vec[3];
        model_map_[ques.id_]=ques;
      }
      file.close();
      return true;
    }

    bool SplicingCode(std::string user_code,const std::string& ques_id,std::string* code){
      //1.查找下对应id的题目是否存在
      auto iter=model_map_.find(ques_id);
      if(iter===model_map_.end()){
        LOG(ERROR,"can not find question id is")<<ques_id<<std::endl;
        return false;
      }

      std::string tail_code;
      int ret=FileOper::ReadDataFromFile(TailPath(iter->second.path_),)
    }

  private:
    std::string DescPath(const std::string& ques_path){
      return ques_path+"desc.txt";
    }
    std::string HeaderPath(const std::string& ques_path){
      return ques_path+"header.cpp";
    }
  private:
    std::unordered_map<std::string,Question> model_map_; 
};
