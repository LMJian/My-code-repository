#include"httplib.h"
#include"db.hpp"
#include<signal.h>

MYSQL* mysql=NULL;
int main(){
  using namespace httplib;
  using namespace blog_system;
  //1.先和数据库建立连接
  mysql=blog_system::MySQLInit(); 
  signal(SIGINT,[](int){
      blog_system::MySQLRelease(mysql);
      exit(0);
      });
  //2.创建相关数据库处理对象
  BlogTable blog_table(mysql);
  TagTable tag_table(mysql);
  //3.创建文档服务器，并设置路由(HTTP服务器中的路由，和IP协议的路由不一样)此处的路由是把方法+path->>哪个处理函数关联关系声明清楚
  Server server;
  //新增博客
  server.Post("/blog",[&blog_table](const Request& req,Response& resp){
      printf("新增博客！\n");
      //1.获取到请求中的body并解析成json
      Json::Reader reader;
      Json::FastWriter writer;
      Json::Value req_json;
      Json::Value resp_json;
      bool ret=reader.parse(req.body,req_json);
      if(!ret){
        //解析出错，给用户提示
        printf("解析请求失败！%s\n",req.body.c_str());
        //构造一个响应对象，告诉客户端出错了！
        resp_json["ok"]=false;
        resp_json["reason"]="input data parse failed!";
        resp.status=400;
        resp.set_content(writer.write(resp_json),"application/json");
        return;
      }
      //2.对参数进行校验
      if(req_json["title"].empty()||req_json["content"].empty()||req_json["tag_id"].empty()||req_json["create_time"].empty()){
        //请求数据格式出错，给用户提示
        printf("请求数据格式出错！%s\n",req.body.c_str());
        //构造一个响应对象，告诉客户端出错了！
        resp_json["ok"]=false;
        resp_json["reason"]="input data format error!";
        resp.status=400;
        resp.set_content(writer.write(resp_json),"application/json");
        return;
      }
      //3.真正的调用MySQL接口来操作
      ret=blog_table.Insert(req_json);
      if(!ret){
        printf("博客插入失败！");
        resp_json["ok"]=false;
        resp_json["reason"]="blog insert failed!";
        resp.status=500;
        resp.set_content(writer.write(resp_json),"application/json");
        return;
      }
      //4.构造一个正确的响应给客户端即可
      printf("博客插入成功！\n");
      resp_json["ok"]=true;
      resp.set_content(writer.write(resp_json),"application/json");
      return;

    });
  //查看所有博客列表
  server.Get("/blog",[](const Request& req,Response& resp){

      });
  //查看某个博客
  server.Get(R"(/blog/(\d+))",[](const Request& req,Response& resp){

      });
  //修改某个博客
  server.Put(R"(/blog/(\d+))",[](const Request& req,Response& resp){

      });
  //删除
  server.Delete(R"(/blog/(\d+))",[](const Request& req,Response& resp){

      });
  //新增标签
  server.Post("/tag",[](const Request& req,Response& resp){

      });
  //删除标签
  server.Delete(R"(/tag/(\d+))",[](const Request& req,Response& resp){

      });
  //查看所有标签
  server.Get("/tag",[](const Request& req,Response& resp){

      });
  server.set_base_dir("./wwwroot");
  server.listen("0.0.0.0",9093);
  return 0;
}
