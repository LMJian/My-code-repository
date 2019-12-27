//创建一些相关的类来封装数据库操作
//
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<mysql/mysql.h>
#include<jsoncpp/json/json.h>
using namespace std;

namespace blog_system{
  static MYSQL* MySQLInit(){
    //初始化一个mysql句柄并建立连接
    //1.创建句柄
    MYSQL* connect_fd=mysql_init(NULL);
    //2.和数据库建立连接
    if(mysql_real_connect(connect_fd,"127.0.0.1","root","LMJian521","blog_system2",3306,NULL,0)==NULL){
      printf("链接失败！%s\n",mysql_error(connect_fd));
      return NULL;
    }
    //3.设置字符编码
    mysql_set_character_set(connect_fd,"utf8");
    return connect_fd;

  }
  static void MySQLRelease(MYSQL* connect_fd){
    //释放句柄并断开链接
    mysql_close(connect_fd);
  }
  //创建一个类，用于操作博客表的类
  class BlogTable{
    public:
      BlogTable(MYSQL* connect_fd):mysql_(connect_fd){
        //通过这个构造函数获取到一个数据库的操作句柄
         
      }
      //以下操作相关参数都统一使用JSON的方式
      //Json::value表示一个具体的json对象
      //形如：
      //{
      //   title:"博客标题"，
      //   content:"博客正文"，
      //   create_time:"创建时间"，
      //   tag_id:"标签id"
      //}
      bool Insert(const Json::Value& blog){
        const string& content=blog["content"].asString();
        //文档要求to的长度为content.size()*2+1
        char* to=new char[content.size()*2+1];
        mysql_real_escape_string(mysql_,to,content.c_str(),content.size());
        //核心就是拼装sql语句
        char sql[1024*100]={0};
        sprintf(sql,"insert into blog_table values(null,'%s','%s','%d','%s')",blog["title"].asCString(),blog["content"].asCString(),blog["tag_id"].asInt(),blog["create_time"].asCString());
        int ret=mysql_query(mysql_,sql);
        if(ret!=0){
          printf("执行插入博客失败！%s\n",mysql_error(mysql_));
          delete[] to;
          return false;
        }
        delete[] to;
        return true;
      }
      //blogs作为一个输出型参数
      bool SelectAll(Json::Value* blogs,const std::string& tag_id){
        return true;
      }
      //blog同样是输出型参数，根据当前的blog_id在数据库中找到具体的
      //博客内容通过blog参数返回给调用者
      bool SelectOne(int32_t blog_id,Json::Value* blog){
        return true;
      }
      bool Update(const Json::Value& blog){
        return true;
      }
      bool Delete(int32_t blog_id){
        return true;
      }
    private:
      MYSQL* mysql_;

  };
  class TagTable{
    public:
      TagTable(){

      }
      bool Insert(const Json::Value& tag){
        return true;
      }
      bool Delete(int32_t tag_id){
        return true;
      }
      bool SelectAll(Json::Value* tags){
        return true;
      }

private:

  };
}//end blog_system
