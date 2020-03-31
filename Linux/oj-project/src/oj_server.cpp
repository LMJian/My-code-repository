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
      std::vector<Question> ques;
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
  //                  arr[0]=12
  //                  arr[1]=13
  //                  arr[2]=14
  //                  arr[0] 12-13-14
  //源码转义：特殊字符就按照字符字面译码
  //      R"(str)"
  svr.Get(R"(/question/(\d+))",[&ojmodel](const Request& req,Response& resp){
      //1.去试题模块去查找对应题号的具体的题目信息
      //    map当中(序号 名称 题目的地址 难度)
      
      std::string desc;
      std::string header;
      //从querystr当中获取id
      LOG(INFO,"req.matches")<<req.matches[0]<<":"<<req.matches[1]<<std::endl;
      //2. 在题目地址的路径下去加载单个题目的描述信息
      struct Question ques;
      ojmodel.GetOneQuestion(req.matches[1].str(),&desc,&header,&ques);
      //3. 进行组织，返回给浏览器
      std::string html="1";
      resp.set_content(html,"text/html;charset=UTF-8");
      });
  svr.Post(R"(/question/(\d+))",[&ojmodel](const Request& req,Response& resp){
      //key:value
      //1.从正文当中提取出来未提交的内容，主要是提取code字段所对应的内容
      //   提交的内容当中有url编码--->提交内容进行解码
      LOG(INFO,req.body);
      //2.编译&运行
      //3.构造响应，json
      std::string html="1";
      resp.set_content(html,"text/html; charset=UTF-8");
      });
  LOG(INFO,"listen in 0.0.0.0:9090")<<std::endl;
  LOG(INFO,"Server ready")<<std::endl;
  svr.listen("0.0.0.0",9090);
  return 0;
}
