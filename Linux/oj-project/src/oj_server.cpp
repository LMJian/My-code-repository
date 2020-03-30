#include<stdio.h>
#include<string>
#include<string.h>
#include"httplib.h"
#include"oj_model.hpp"
#include"oj_view.hpp"
#include"oj_log.hpp"

int main(){
  //httplib的时候，需要使用httplib的命名空间
  using namespace httplib;
  Server svr;
  OjModel ojmodel;
  //给http传递lamdba表达式是一个回调函数的方式
  //1.获取试题信息
  //试题信息来源于文件中
  
  svr.Get("/all_questions",[&ojmodel](const Request& req,Response& resp){
      std::vector<Questions> ques;
      ojmodel.GetAllQuestions(&ques);
      //<html>id.name start</html>
      //char buf[10240]={'\0'};
      //printf("%lu\n",ques.size());
      //if(ques.size()==1){
      //  snprintf(buf,sizeof(buf)-1,"<html>%s.%s %s</html>",ques[0].id_.c_str(),ques[0].name_.c_str(),ques[0].star_.c_str());
      //}
      //std::string html;
      //html.assign(buf,strlen(buf));

      //使用模板技术填充html页面
      std::string html;
      OjView::ExpandAllQuestionshtml(&html,ques);
      //LOG(INFO,html);
      resp.set_content(html,"text/html;charset=UTF-8");
      });
  //正则表达式
  //      \b：单词的分界
  //      *：匹配任意字符串
  //      \d:匹配一个数字
  //      ():分组应用(\d+)-(\d+)-(\d+)
  //                  12 -  13 -  14
  //                  arr[1]=12
  //                  arr[2]=13
  //                  arr[2]=14
  //                  arr[0] 12-13-14
  //源码转义：特殊字符就按照字符字面译码
  //      R"(str)"
  svr.Get(R"(/question/\d+)",[&ojmodel](const Request& req,Response& resp){
      //1.去试题模块去查找对应题号的具体的题目信息
      //    map当中(序号 名称 题目的地址 难度)
      
      std::string desc;
      std::string header;
      //从querystr当中获取id
      printf("path:%s\n",req.path.c_str());
      LOG(INFO,"req.matches")<<req.matches[0]<<":"<<req.matches[1]<<":"<<std::endl;
      ojmodel.GetOneQuestion(req.matches[1].str(),&desc,&header);

      //2. 在题目地址的路径下去加载单个题目的描述信息，进行组织，返回给浏览器
      std::string html;
      OjView::ExpandOneQuestion(xx,desc,header,&html);
      resp.set_content(html,"text/html;charset=UTF-8");
      });
  LOG(INFO,"listen in 0.0.0.0:9090");
  LOG(INFO,"Server ready");
  svr.listen("0.0.0.0",9090);
  return 0;
}
