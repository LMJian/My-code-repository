#include"httplib.h"
#include"db.hpp"
#include<signal.h>


int main(){
  using namespace httplib;
  //1.创建数据库处理对象 
  BlogTable blog_table;
  TagTable tag_table;
  //2.创建服务器
  Server server;
  //新增博客
  server.Post("/blog",[&blog_table](const Request& req,Response& resp){
      printf("新增博客！\n");
      Json::Reader reader;
      Json::FastWriter writer;
      Json::Value req_json;
      Json::Value resp_json;
      //将请求中的body解析成Json，如果解析错误，构造一个响应对象
      bool ret=reader.parse(req.body,req_json);
      if(!ret){
        printf("解析请求失败！%s\n",req.body.c_str());
        resp_json["ok"]=false;
        resp_json["reason"]="Blog post reader.parse failed!";
        resp.status=400;
        resp.set_content(writer.write(resp_json),"application/json");
        return;
      }
      //对参数进行校验，如果错误，够着一个响应对象
      if(req_json["title"].empty()||req_json["content"].empty()||req_json["create_time"].empty()||req_json["tag_id"].empty()){
        printf("请求格式错误！%s\n",req.body.c_str());
        resp_json["ok"]=false;
        resp_json["reason"]="Blog post resp_json is empty!";
        resp.status=400;
        resp.set_content(writer.write(resp_json),"application/json");
        return;
      }
      //调用mysql接口来操作
      ret=blog_table.Insert(req_json);
      if(!ret){
        printf("插入博客失败！");
        resp_json["ok"]=false;
        resp_json["reason"]="Blog post insert failed!";
        resp.status=500;
        resp.set_content(writer.write(resp_json),"application/json");
        return;
      }
      //构造成功的响应
      printf("博客插入成功！\n");
      resp_json["ok"]=true;
      resp.set_content(writer.write(resp_json),"application/json");
      return;
  });
  //查看所有博客
  server.Get("/blog",[&blog_table](const Request& req,Response& resp){
      printf("查看所有博客！\n");
      Json::FastWriter writer;
      Json::Value resp_json;
      const std::string& tag_id=req.get_param_value("tag_id");
      //调用mysql接口
      bool ret=blog_table.SelectAll(resp_json,tag_id);
      if(!ret){
        printf("查看所有博客失败！\n");
        resp_json["ok"]=false;
        resp_json["reason"]="Blog SelectAll failed!";
        resp.status=500;
        resp.set_content(writer.write(resp_json),"application/json");
        return;
      }
      //返回成功的响应
      printf("查询所有博客成功！");
      resp.set_content(writer.write(resp_json),"application/json");
      return;
  });
  //查询指定博客
  server.Get(R"(/blog/(\d+))",[&blog_table](const Request& req,Response& resp){
      Json::FastWriter writer;
      Json::Value resp_json;
      const int32_t blog_id=std::stoi(req.matches[1].str());
      printf("查看id=%d的博客!\n",blog_id);
      //调用mysql接口
      bool ret=blog_table.SelectOne(resp_json,blog_id);
      if(!ret){
        resp_json["ok"]=false;
        resp_json["reason"]="Blog SelectOne failed!";
        resp.status=404;
        resp.set_content(writer.write(resp_json),"application/json");
        return;
      }
      //返回成功响应
      printf("查询成功！");
      resp.set_content(writer.write(resp_json),"application/json");
      return;
  });
  //修改指定博客
  server.Put(R"(/blog/(\d+))",[&blog_table](const Request& req,Response& resp){
      Json::Reader reader;
      Json::Value req_json;
      Json::FastWriter writer;
      Json::Value resp_json;
      const int32_t blog_id=std::stoi(req.matches[1].str());
      printf("修改id=%d的博客！\n",blog_id);
      //解析请求中的body解析成json,错误则构造一个响应对象
      bool ret=reader.parse(req.body,req_json);
      if(!ret){
        printf("解析失败！"); 
        resp_json["ok"]=false;
        resp_json["reason"]="Blog put reader.parse failed!";
        resp.status=400;
        resp.set_content(writer.write(resp_json),"application/json");
        return;
      }
      //对参数进行校验，如果错误，够着一个响应对象
      if(req_json["title"].empty()||req_json["content"].empty()||req_json["tag_id"].empty()){
        printf("请求格式错误！%s\n",req.body.c_str());
        resp_json["ok"]=false;
        resp_json["reason"]="Blog put resp_json is empty!";
        resp.status=400;
        resp.set_content(writer.write(resp_json),"application/json");
        return;
      }
      //调用mysql接口
      req_json["blog_id"]=blog_id;
      ret=blog_table.Update(req_json);
      if(!ret){
        printf("修改失败！");
        resp_json["ok"]=false;
        resp_json["reason"]="Blog Update failed!";
        resp.status=500;
        resp.set_content(writer.write(resp_json),"application/json");
        return;
      }
      printf("修改成功！");
      resp_json["ok"]=true;
      resp.set_content(writer.write(resp_json),"application/json");
      return;
  });
  //删除博客
  server.Delete(R"(/blog/(\d+))",[&blog_table](const Request& req,Response& resp){
      int32_t blog_id=stoi(req.matches[1].str());
      printf("删除id=%d的博客",blog_id);
      Json::FastWriter writer;
      Json::Value resp_json;
      //调用mysql接口来操作
      bool ret=blog_table.Delete(blog_id);
      if(!ret){
        printf("删除博客失败!\n");
        resp_json["ok"]=false;
        resp_json["reason"]="Blog Delete failed!";
        resp.status=500;
        resp.set_content(writer.write(resp_json),"application/json");
        return;
      }
      printf("删除成功!");
      resp_json["ok"]=true;
      resp.set_content(writer.write(resp_json),"application/json");
      return;
  });
  //插入标签
  server.Post("/tag",[&tag_table](const Request& req,Response& resp){
      printf("新增标签！\n");
      Json::Reader reader;
      Json::FastWriter writer;
      Json::Value req_json;
      Json::Value resp_json;
      //将请求中的body解析成Json，如果解析错误，构造一个响应对象
      bool ret=reader.parse(req.body,req_json);
      if(!ret){
        printf("解析请求失败！%s\n",req.body.c_str());
        resp_json["ok"]=false;
        resp_json["reason"]="Tag post reader.parse failed!";
        resp.status=400;
        resp.set_content(writer.write(resp_json),"application/json");
        return;
      }
      //对参数进行校验，如果错误，够着一个响应对象
      if(req_json["tag_name"].empty()){
        printf("请求格式错误！%s\n",req.body.c_str());
        resp_json["ok"]=false;
        resp_json["reason"]="Tag post resp_json is empty!";
        resp.status=400;
        resp.set_content(writer.write(resp_json),"application/json");
        return;
      }
      //调用mysql接口来操作
      ret=tag_table.Insert(req_json);
      if(!ret){
        printf("插入标签失败！");
        resp_json["ok"]=false;
        resp_json["reason"]="Tag Insert failed!";
        resp.status=500;
        resp.set_content(writer.write(resp_json),"application/json");
        return;
      }
      //构造成功的响应
      printf("标签插入成功！\n");
      resp_json["ok"]=true;
      resp.set_content(writer.write(resp_json),"application/json");
      return;
  });
  //删除标签
  server.Delete(R"(/tag/(\d+))",[&tag_table](const Request& req,Response& resp){
      int32_t tag_id=std::stoi(req.matches[1].str());
      printf("删除id=%d的标签!\n",tag_id);
      Json::FastWriter writer;
      Json::Value resp_json;
      //调用mysql接口来操作
      bool ret=tag_table.Delete(tag_id);
      if(!ret){
        printf("删除标签失败!\n");
        resp_json["ok"]=false;
        resp_json["reason"]="Tag delete failed!";
        resp.status=500;
        resp.set_content(writer.write(resp_json),"application/json");
        return;
      }
      printf("删除成功!");
      resp_json["ok"]=true;
      resp.set_content(writer.write(resp_json),"application/json");
      return;
    }); 
  //查看所有标签
  server.Get("/tag",[&tag_table](const Request& req,Response& resp){
      (void)req;
      printf("查看所有标签！\n");
      Json::FastWriter writer;
      Json::Value resp_json;
      //调用mysql接口
      bool ret=tag_table.SelectAll(resp_json);
      if(!ret){
        printf("查看所有标签失败！\n");
        resp_json["ok"]=false;
        resp_json["reason"]="Tag SelectAll failed!";
        resp.status=500;
        resp.set_content(writer.write(resp_json),"application/json");
        return;
      }
      //返回成功的响应
      printf("查询所有标签成功！");
      resp.set_content(writer.write(resp_json),"application/json");
      return;
  }); 
  server.set_base_dir("./wwwroot");
  server.listen("0.0.0.0",9093);
  return 0;
}
