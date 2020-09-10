//MVC => model: 负责数据存储

//约定以文件的形式存储题目信息
//所有题目的 题目序号，题目名称，题目难度，题目所在路径，保存在oj_data/oj_config.cfg文件中
//约定每个题目在oj_data目录中就对应着一个目录，目录的名字为题目的id
//主要包含以下几个文件：
//1)  desc.txt    题目描述
//2） header.cpp  代码框架
//3） tail.cpp    代码测试用例

#pragma once
#include<vector>
#include<string>
#include<map>
#include<fstream>
#include"util.hpp"

struct Question{
    std::string id;    //题目序号
    std::string name;  //题目名称
    std::string dir;   //题目所在路径
    std::string star;  //题目难度

    //一个题目的详细信息
    std::string desc;       //题目描述
    std::string header_cpp; //代码框架
    std::string tail_cpp;   //测试用例
};

class OjModel{
private:
    //使用map来组织题目的数据信息       id : Question
    std::map<std::string,Question> model_;

public:
    //加载题库到内存中，用map来组织数据
    bool Load(){
        //1. 打开oj_config.cfg文件
        std::ifstream file("./oj_data/oj_config.cfg");
        if(!file.is_open()){
            return false;
        }
        //2. 按行读取oj_config.cfg文件
        std::string line;
        while(std::getline(file,line)){
            //3. 解析每个题目的信息   （题目序号，题目名称，题目难度，题目所在路径）
            std::vector<std::string> tokens;
            //   调用自己封装的工具类进行解析    约定间隔为四个空格
            StringUtil::Split(line,"    ",&tokens);
            if(tokens.size()!=4){
                LOG(ERROR) << "config file format error!\n";
                continue;
            }
            //4. 填充结构体，把结构体加入到map中
            Question q;
            q.id = tokens[0];
            q.name = tokens[1];
            q.star = tokens[2];
            q.dir = tokens[3];
            //   调用自己封装的工具类读取文件，写入结构体
            FileUtil::Read(q.dir+"/desc.txt",&q.desc);
            FileUtil::Read(q.dir+"/header.hpp",&q.header_cpp);
            FileUtil::Read(q.dir+"/tail.cpp",&q.tail_cpp);
            model_[q.id] = q;
        }
        file.close();
        LOG(INFO) << "Load " << model_.size() << " questions\n";
        return true;
    }

    //获取所有题目信息
    bool GetAllQuestions(std::vector<Question>* questions) const{
        questions->clear();
        for(const auto& kv : model_){
            questions->push_back(kv.second);
        }
        return true;
    }

    //获取指定id的题目信息
    bool GetQuestion(const std::string& id,Question* q) const{
        const auto pos = model_.find(id);
        if(pos == model_.end()){
            return false;
        }
        *q = pos->second;
        return true;
    }
};