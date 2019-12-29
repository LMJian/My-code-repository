//创建一些相关的类来封装数据库操作
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<memory>
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
        //char* to=new char[content.size()*2+1];
        unique_ptr<char> to(new char[content.size()*2+1]);
        //**获取MySQL真正的转移字符串**
        mysql_real_escape_string(mysql_,to.get(),content.c_str(),content.size());
        //核心就是拼装sql语句
        unique_ptr<char> sql(new char[content.size()*2+4096]);
        //char sql[1024*100]={0};
        sprintf(sql.get(),"insert into blog_table values(null,'%s','%s','%d','%s')",blog["title"].asCString(),to.get(),blog["tag_id"].asInt(),blog["create_time"].asCString());
        int ret=mysql_query(mysql_,sql.get());
        if(ret!=0){
          printf("执行插入博客失败！%s\n",mysql_error(mysql_));
          return false;
        }
        printf("执行插入博客成功!\n");
        return true;
      }
      //blogs作为一个输出型参数
      bool SelectAll(Json::Value* blogs,const std::string& tag_id=""){
        //查找不需要太长的长度
        char sql[1024*4]={0};
        if(tag_id==""){
          //此时不需要按照tag来筛选结果
          sprintf(sql,"select blog_id,title,tag_id,create_time from blog_table");
        }
        else{
          //此时需要按照tag来筛选
          sprintf(sql,"select blog_id,title,tag_id,create_time from blog_table where tag_id=%d",stoi(tag_id));
        }
        int ret=mysql_query(mysql_,sql);
        if(ret!=0){
          printf("执行查找所有博客失败!%s\n",mysql_error(mysql_));
          return false;
        }
        printf("执行查找所有博客成功！\n");
        MYSQL_RES* result=mysql_store_result(mysql_);
        int rows=mysql_num_rows(result);
        //遍历结果集合然后把结果写回到blogs参数中，返回调用者
        for(int i=0;i<rows;++i){
          MYSQL_ROW row=mysql_fetch_row(result);
          Json::Value blog;
          //row[]中的下标和上面的select语句中写的列的顺序是相关联的
          blog["blog_id"]=atoi(row[0]);
          blog["title"]=row[1];
          blog["tag_id"]=atoi(row[2]);
          blog["create_time"]=row[3];
          blogs->append(blog);
        }
        //mysql查询的结果集合需要及时释放
        mysql_free_result(result);
        printf("执行查找所有博客成功！共查找到%d条博客\n",rows);
        return true;
      }
      //blog同样是输出型参数，根据当前的blog_id在数据库中找到具体的
      //博客内容通过blog参数返回给调用者
      bool SelectOne(int32_t blog_id,Json::Value* blog){
        char sql[1024]={0};
        sprintf(sql,"select blog_id,title,content,tag_id,create_time from blog_table where blog_id=%d",blog_id);
        int ret=mysql_query(mysql_,sql);
        if(ret!=0){
          printf("执行查找博客失败！%s\n",mysql_error(mysql_));
          return false;
        }
        MYSQL_RES* result=mysql_store_result(mysql_);
        int rows=mysql_num_rows(result);
        if(rows!=1){
          printf("查找到的博客不是只有一条！实际有%d条\n",rows);
          return false;
        }
        MYSQL_ROW row=mysql_fetch_row(result);
        (*blog)["blog_id"]=atoi(row[0]);
        (*blog)["title"]=row[1];
        (*blog)["content"]=row[2];
        (*blog)["tag_id"]=atoi(row[3]);
        (*blog)["create_time"]=row[4];
        return true;
      }
      bool Update(const Json::Value& blog){
        const string& content=blog["content"].asString();
        //文档要求to的长度为content.size()*2+1
        //char* to=new char[content.size()*2+1];
        unique_ptr<char> to(new char[content.size()*2+1]);
        mysql_real_escape_string(mysql_,to.get(),content.c_str(),content.size());
        
        //核心就是拼装sql语句
        unique_ptr<char> sql(new char[content.size()*2+4096]);
        sprintf(sql.get(),"update blog_table set title='%s',content='%s',tag_id=%d where blog_id=%d",blog["title"].asCString(),to.get(),blog["tag_id"].asInt(),blog["blog_id"].asInt());
        int ret=mysql_query(mysql_,sql.get());
        if(ret!=0){
          printf("更新博客失败！%s\n",mysql_error(mysql_));
          return false;
        }
        printf("更新博客成功！\n");
        return true;
      }
      bool Delete(int32_t blog_id){
        char sql[1024*4]={0};
        sprintf(sql,"delete from blog_table where blog_id=%d",blog_id);
        int ret=mysql_query(mysql_,sql);
        if(ret!=0){
          printf("删除博客失败!%s\n",mysql_error(mysql_));
          return false;
        }
        return true;
      }
    private:
      MYSQL* mysql_;
  };

  class TagTable{
    public:
      TagTable(MYSQL* mysql)
      :mysql_(mysql)
      {}
      bool Insert(const Json::Value& tag){
        char sql[1024*4]={0};
        sprintf(sql,"insert into tag_table values(null,'%s')",tag["tag_name"].asCString());
        int ret=mysql_query(mysql_,sql);
        if(ret!=0){
          sprintf(sql,"插入标签失败！%s\n",mysql_error(mysql_));
          return false;
        }
        printf("插入标签成功！\n");
        return true;
      }
      bool Delete(int32_t tag_id){
        char sql[1024*4]={0};
        sprintf(sql,"delete from tag_table where tag_id=%d",tag_id);
        int ret=mysql_query(mysql_,sql);
        if(ret!=0){
          printf("删除标签失败！%s\n",mysql_error(mysql_));
          return false;
        }
        printf("删除标签成功!\n");
        return true;
      }
      bool SelectAll(Json::Value* tags){
        char sql[1024*4]={0};
        sprintf(sql,"select tag_id,tag_name from tag_table");
        int ret=mysql_query(mysql_,sql);
        if(ret!=0){
          printf("查找标签失败！%s\n",mysql_error(mysql_));
          return false;
        }
        MYSQL_RES* result=mysql_store_result(mysql_);
        int rows=mysql_num_rows(result);
        for(int i=0;i<rows;++i){
          MYSQL_ROW row=mysql_fetch_row(result);
          Json::Value tag;
          tag["tag_id"]=atoi(row[0]);
          tag["tag_name"]=row[1];
          tags->append(tag);
        }
        printf("查找标签成功！共找到%d个！\n",rows);
        return true;
      }
private:
      MYSQL* mysql_;
  };
}//end blog_system
