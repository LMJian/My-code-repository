#include"db.hpp"

void TestBlogTable(){
  blog_table blog;
  Json::StyledWriter writer;
  bool ret=false;
  
  //测试插入
  /*Json::Value test;
  test["title"]="我的第一篇博客";
  test["content"]="我要成为大佬";
  test["tag_id"]=1;
  ret=blog.Insert(test);
  printf("insert:%d\n",ret);*/
  
  //测试查找
  Json::Value val;
  /*ret=blog.SelectAll(val);
  printf("SelectAll %d\n",ret);
  printf("blogs:%s\n",writer.write(val).c_str());*/

  //测试查找单个博客
  /*ret=blog_table.SelectOne(1,&blog);
  printf("select one %d\n",ret);
  printf("blog:%s\n",writer.write(blog).c_str());*/

  //测试修改博客
  /*val["blog_id"]=1;
  val["title"]="第一篇C语言博客";
  val["content"]="1.变量和类型\n什么是变量？创建一'变量'就相当于创建一块内存空间";
  val["tag_id"]=666;
  ret=blog.Update(val);
  printf("update %d\n",ret);*/

  //测试删除博客
  ret=blog.Delete(1);
  printf("delete %d\n",ret);
}
void TestTagTable(){
  Json::StyledWriter writer;
  TagTable tag;

  //测试插入
  /*Json::Value val;
  val["tag_name"]="C语言";
  bool ret=tag.Insert(val);
  printf("insert %d\n",ret);*/

  //测试查找
  /*Json::Value val;
  bool ret=tag.SelectAll(val);
  printf("select all %d\n",ret);
  printf("val:%s\n",writer.write(val).c_str());*/
  
  //测试删除
  bool ret=tag.Delete(1);
  printf("delete %d\n",ret);
}
int main(){
  //TestBlogTable();
  TestTagTable();
  return 0;
}
