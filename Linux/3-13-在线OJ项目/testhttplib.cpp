#include<stdio.h>
#include"httplib.h"

using namespace httplib;

void func(const Request& req,Response& resp){
  //req:http请求的内容
  //resp:需要给用户响应的内容
  resp.set_content("<html>hello world</html>","123");
}

int main(){
  Server svr;

  svr.Get("/",[](const Request& req,Response& resp){
      (void)req;
      resp.set_content("<html>hello offer</html>","123");

      });
  svr.listen("0.0.0.0",19999);

  return 0;
}
