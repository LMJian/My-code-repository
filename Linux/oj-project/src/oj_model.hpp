//model?
//MVC 
//M => model:负责数据存储
//V => view:负责显示页面
//C => controller: 核心业务逻辑

//基于文件的方式完成题目的存储
//约定每一个题目对应一个目录，目录的名字就是题目的id
//目录里面包含以下几个文件：
//1） header.cpp 代码框架
//2） tail.cpp 代码测试用例
//3)  desc.txt 题目详细描述
//除此之外，再搞一个oj_config.cfg文件，作为一个总的入口文件
//这个文件是一个行文本文件，
//这个文件的每一行对应一个需要被服务器加载起来的题目
//这一行里面包含以下几个信息：题目的id，题目的名字，题目的难度，题目对应的目录
#pragma once
#include<vector>
#include<string>
#include<map>
#include<fstream>
#include"util.hpp"
//model这个模块要做的事情就是吧刚才在文件中存储
//的题目信息加载起来，供服务器随时使用

struct Question{
    std::string id;
    std::string name;
    std::string dir;   //题目目录，就包含了题目描述、题目的代码框架，题目的测试用例
    std::string star;  //难度

    //以下这几个字段要根据dir字段来获取到
    std::string desc;  //题目的描述
    std::string header_cpp;  //题目的代码框架中的代码
    std::string tail_cpp;   //题目的测试用例代码
};

class OjModel{
private:
    std::map<std::string,Question> model_;

public:
    //在文件上的数据加载到内存中，加到哈希表中
    bool Load(){
        //1.先打开oj_config.cfg文件
        std::ifstream file("./oj_data/oj_config.cfg");
        if(!file.is_open()){
            return false;
        }
        //2.按行读取oj_config.cfg文件，并且解析
        std::string line;
        while(std::getline(file,line)){
            //3.根据解析结果拼装成question结构体
            std::vector<std::string> tokens;
            StringUtil::Split(line,"    ",&tokens);
            if(tokens.size()!=4){
                LOG(ERROR) << "config file format error!\n";
                continue;
            }
            //4.把结构体加入到hash表中
            Question q;
            q.id = tokens[0];
            q.name = tokens[1];
            q.star = tokens[2];
            q.dir = tokens[3];
            FileUtil::Read(q.dir+"/desc.txt",&q.desc);
            FileUtil::Read(q.dir+"/header.hpp",&q.header_cpp);
            FileUtil::Read(q.dir+"/tail.cpp",&q.tail_cpp);
            model_[q.id] = q;
        }
        file.close();
        LOG(INFO) << "Load " << model_.size() << " questions\n";
        return true;
    }
    bool GetAllQuestions(std::vector<Question>* questions)const{
        //遍历哈希表
        questions->clear();
        for(const auto& kv : model_){
            questions->push_back(kv.second);
        }
        return true;
    }

    bool GetQuestion(const std::string& id,Question* q){
        auto pos = model_.find(id);
        if(pos == model_.end()){
            return false;
        }
        *q = pos->second;
        return true;
    }
};