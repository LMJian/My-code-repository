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
public:
    bool GetAllQuestions(std::vector<Question>* questions){
        return true;
    }
    bool GetQuestion(const std::string& id,Question* q){
        return true;
    }
    //在文件上的数据加载起来
    bool Load(){
        return true;
    }
};