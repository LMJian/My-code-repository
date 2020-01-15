#include"db.hpp"

void TestBlogTable(){
  //blog_table blog;
  //Json::StyledWriter writer;
  //bool ret=false;
  
  //测试插入
  /*Json::Value test;
  test["title"]="我的第一篇博客";
  test["content"]="我要成为大佬";
  test["tag_id"]=1;
  ret=blog.Insert(test);
  printf("insert:%d\n",ret);*/
  
  //测试查找
  //Json::Value val;
  //ret=blog.SelectAll(val);
  //printf("SelectAll %d\n",ret);
  //printf("blogs:%s\n",writer.write(val).c_str());

  //测试查找单个博客
  /*ret=blog.SelectOne(val,5);
  printf("select one %d\n",ret);
  printf("blog:%s\n",writer.write(val).c_str());*/

  //测试修改博客
  /*val["blog_id"]=5;
  val["title"]="想家";
  val["content"]="我好想回家";
  val["tag_id"]=666;
  ret=blog.Update(val);
  printf("update %d\n",ret);*/

  //测试删除博客
  //ret=blog.Delete(5);
  //printf("delete %d\n",ret);
}
void TestTagTable(){
  Json::StyledWriter writer;
  TagTable tag;

  //测试插入
  /*Json::Value val;
  val["tag_name"]="家";
  bool ret=tag.Insert(val);
  printf("insert %d\n",ret);*/

  //测试查找
  Json::Value val;
  bool ret=tag.SelectAll(val);
  printf("select all %d\n",ret);
  printf("val:%s\n",writer.write(val).c_str());
  
  //测试删除
  //bool ret=tag.Delete(1);
  //printf("delete %d\n",ret);
}
int main(){
  //TestBlogTable();
  //TestTagTable();
  return 0;
}
