#include"httplib.h"
#include"oj_model.hpp"

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
      //使用模板技术填充html页面
      resp.set_content("","text/html");
      });
  svr.listen("0.0.0.0",9090);
  return 0;
}
