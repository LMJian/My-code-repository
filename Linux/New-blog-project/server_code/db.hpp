#include<stdio.h>
#include<stdlib.h>
#include<mysql/mysql.h>
#include<jsoncpp/json/json.h>
#include<string>
#include<memory>

class blog_table{
  public:
    blog_table()
    :connect_fd_(nullptr){
      //1.创建数据库连接句柄
      //MYSQL *mysql_init(MYSQL *mysql)
      connect_fd_=mysql_init(NULL);
      if(connect_fd_==NULL){
        printf("mysql init error:%s\n",mysql_error(connect_fd_));
        mysql_close(connect_fd_);
      }
      printf("句柄创建成功！\n");
      //2.和数据库建立连接
      //MYSQL *mysql_real_connect(MYSQL *mysql, const char *host, const char *user, const char *passwd, const char *db, unsigned int port, const char *unix_socket, unsigned long client_flag)
      if(mysql_real_connect(connect_fd_, "127.0.0.1", "root", "LMJian521", "blog_db", 3306, NULL,1)==NULL){
        printf("mysql real connect error:%s\n",mysql_error(connect_fd_));
        mysql_close(connect_fd_);
      }
      printf("数据库连接成功！\n");
      //3.设置编码方式
      //mysql_set_character_set(MYSQL*,const char*)
      mysql_set_character_set(connect_fd_,"utf8");
    }
    ~blog_table(){
      //5.关闭数据库句柄
      //void mysql_close(MYSQL *mysql)
      mysql_close(connect_fd_);
    }
    bool Insert(const Json::Value& blog){
      //拼接sql语句
      const std::string& connect=blog["content"].asString();
      std::unique_ptr<char> to(new char[connect.size()*2+1]);
      //获取mysql真正的转义字符串,mysql文档要求to的大小为2*connect.size()+1
      //unsigned long mysql_real_escape_string(MYSQL *mysql, char *to, const char *from, unsigned long length)
      mysql_real_escape_string(connect_fd_,to.get(), connect.c_str(), connect.size());
      std::unique_ptr<char> buf(new char[connect.size()*2+4096]);
      sprintf(buf.get(),"insert into blog_tb(title,content,tag_id) value('%s','%s',%d);",blog["title"].asCString(),to.get(),blog["tag_id"].asInt());
      printf("sql:%s\n",buf.get());
      //4.让服务器执行sql语句
      //int mysql_query(MYSQL *mysql, const char *stmt_str)
      if(mysql_query(connect_fd_,buf.get())!=0){
        printf("mysql_query error:%s\n",mysql_error(connect_fd_));
        mysql_close(connect_fd_);
        return false;
      }
      printf("插入成功!\n");
      return true;
    }
    bool Delete(const int blog_id){
      //拼接sql语句
      char buf[1024]={0};
      sprintf(buf,"delete from blog_tb where blog_id=%d;",blog_id);
      printf("sql:%s\n",buf);
      //4.让服务器执行sql语句
      //int mysql_query(MYSQL *mysql, const char *stmt_str)
      if(mysql_query(connect_fd_,buf)!=0){
        printf("mysql_query error:%s\n",mysql_error(connect_fd_));
        mysql_close(connect_fd_);
        return false;
      }
      printf("删除成功!\n");
      return true;
    }
    bool Update(const Json::Value blog){
      //拼接sql语句
      const std::string& connect=blog["content"].asString();
      std::unique_ptr<char> to(new char[connect.size()*2+1]);
      //获取mysql真正的转义字符串,mysql文档要求to的大小为2*connect.size()+1
      //unsigned long mysql_real_escape_string(MYSQL *mysql, char *to, const char *from, unsigned long length)
      mysql_real_escape_string(connect_fd_,to.get(), connect.c_str(), connect.size());
      std::unique_ptr<char> buf(new char[connect.size()*2+4096]);
      sprintf(buf.get(),"update blog_tb set title='%s',content='%s',tag_id=%d where blog_id=%d;",blog["title"].asCString(),to.get(),blog["tag_id"].asInt(),blog["blog_id"].asInt());
      printf("sql:%s\n",buf.get());
      //4.让服务器执行sql语句
      //int mysql_query(MYSQL *mysql, const char *stmt_str)
      if(mysql_query(connect_fd_,buf.get())!=0){
        printf("mysql_query error:%s\n",mysql_error(connect_fd_));
        mysql_close(connect_fd_);
        return false;
      }
      printf("修改成功!\n");
      return true;
    }
    bool SelectOne(Json::Value& blogs,const int blog_id){
      //拼接sql语句
      char buf[1024]={0};
      sprintf(buf,"select * from blog_tb where blog_id=%d;",blog_id);
      printf("sql:%s\n",buf);
      //4.让服务器执行sql语句
      //int mysql_query(MYSQL *mysql, const char *stmt_str)
      if(mysql_query(connect_fd_,buf)!=0){
        printf("mysql_query error:%s\n",mysql_error(connect_fd_));
        mysql_close(connect_fd_);
        return false;
      }
      printf("sql语句执行成功！\n");
      //5.遍历结果集合
      //MYSQL_RES *mysql_store_result(MYSQL *mysql)
      MYSQL_RES* res=mysql_store_result(connect_fd_);
      if(res==NULL){
        printf("mysql store result error:%s\n",mysql_error(connect_fd_));
        mysql_close(connect_fd_);
        return false;
      }
      //6.获取行数
      //my_ulonglong mysql_num_rows(MYSQL_RES *result)
      int rows=mysql_num_rows(res);
      if(rows>1){
        printf("所查找的并不只有一个，其实上有%d个！\n",rows);
        return false;
      }
      //7.获取一行的数据
      //MYSQL_ROW mysql_fetch_row(MYSQL_RES *result)
      MYSQL_ROW arr=mysql_fetch_row(res);
      Json::Value val;
      val["blog_id"]=atoi(arr[0]);
      val["title"]=arr[1];
      val["content"]=arr[2];
      val["create_time"]=arr[3];
      if(arr[4]!=NULL)
        val["tag_id"]=atoi(arr[4]);
      blogs.append(val); 
      printf("查找到了唯一的信息！\n");
      //8.释放结果集合
      //void mysql_free_result(MYSQL_RES *result)
      mysql_free_result(res);
      return true;
    }
    bool SelectAll(Json::Value& blogs,const std::string& tag_id=""){
      //拼接sql语句
      char buf[1024]={0};
      if(tag_id==""){
        sprintf(buf,"select * from blog_tb;");
      }
      else{
        sprintf(buf,"select * from blog_tb where tag_id=%d;",stoi(tag_id));
      }
      printf("sql:%s\n",buf);
      //4.让服务器执行sql语句
      //int mysql_query(MYSQL *mysql, const char *stmt_str)
      if(mysql_query(connect_fd_,buf)!=0){
        printf("mysql_query error:%s\n",mysql_error(connect_fd_));
        mysql_close(connect_fd_);
        return false;
      }
      printf("sql语句成功执行！\n");
      //5.遍历结果集合
      //MYSQL_RES *mysql_store_result(MYSQL *mysql)
      MYSQL_RES* res=mysql_store_result(connect_fd_);
      if(res==NULL){
        printf("mysql store result error:%s\n",mysql_error(connect_fd_));
        mysql_close(connect_fd_);
        return false;
      }
      //6.获取行数
      //my_ulonglong mysql_num_rows(MYSQL_RES *result)
      int rows=mysql_num_rows(res);
      for(int i=0;i<rows;++i){
        //7.获取一行的数据
        //MYSQL_ROW mysql_fetch_row(MYSQL_RES *result)
        MYSQL_ROW arr=mysql_fetch_row(res);
        Json::Value val;
        val["blog_id"]=atoi(arr[0]);
        val["title"]=arr[1];
        val["content"]=arr[2];
        val["create_time"]=arr[3];
        if(arr[4]!=NULL)
          val["tag_id"]=atoi(arr[4]);
        blogs.append(val);
      }
      printf("共查到了%d条信息！\n",rows);
      //8.释放结果集合
      //void mysql_free_result(MYSQL_RES *result)
      mysql_free_result(res);
      return true;
    }
  private:
    MYSQL* connect_fd_;
};//end blog_table

class TagTable{
  public:
    TagTable()
    :connect_fd_(nullptr){
      //1.创建数据库连接句柄
      //MYSQL *mysql_init(MYSQL *mysql)
      connect_fd_=mysql_init(NULL);
      if(connect_fd_==NULL){
        printf("mysql init error:%s\n",mysql_error(connect_fd_));
        mysql_close(connect_fd_);
      }
      printf("句柄创建成功！\n");
      //2.和数据库建立连接
      //MYSQL *mysql_real_connect(MYSQL *mysql, const char *host, const char *user, const char *passwd, const char *db, unsigned int port, const char *unix_socket, unsigned long client_flag)
      if(mysql_real_connect(connect_fd_, "127.0.0.1", "root", "LMJian521", "blog_db", 3306, NULL,1)==NULL){
        printf("mysql real connect error:%s\n",mysql_error(connect_fd_));
        mysql_close(connect_fd_);
      }
      printf("数据库连接成功！\n");
      //3.设置编码方式
      //mysql_set_character_set(MYSQL*,const char*)
      mysql_set_character_set(connect_fd_,"utf8");
    }
    ~TagTable(){
      //5.关闭数据库句柄
      //void mysql_close(MYSQL *mysql)
      mysql_close(connect_fd_);
    }
    bool Insert(const Json::Value& tag){
      //拼接sql语句
      char buf[1024]={0};
      sprintf(buf,"insert into tag_tb(tag_name) value('%s');",tag["tag_name"].asCString());
      printf("sql:%s\n",buf);
      //4.让服务器执行sql语句
      //int mysql_query(MYSQL *mysql, const char *stmt_str)
      if(mysql_query(connect_fd_,buf)!=0){
        printf("mysql_query error:%s\n",mysql_error(connect_fd_));
        mysql_close(connect_fd_);
        return false;
      }
      printf("插入成功!\n");
      return true;
    }
    bool Delete(const int tag_id){
      //拼接sql语句
      char buf[1024]={0};
      sprintf(buf,"delete from tag_tb where tag_id=%d;",tag_id);
      printf("sql:%s\n",buf);
      //4.让服务器执行sql语句
      //int mysql_query(MYSQL *mysql, const char *stmt_str)
      if(mysql_query(connect_fd_,buf)!=0){
        printf("mysql_query error:%s\n",mysql_error(connect_fd_));
        mysql_close(connect_fd_);
        return false;
      }
      printf("删除成功!\n");
      return true;
    }
    bool SelectAll(Json::Value& tag){
      //拼接sql语句
      char buf[1024]={0};
      sprintf(buf,"select * from tag_tb;");
      printf("sql:%s\n",buf);
      //4.让服务器执行sql语句
      //int mysql_query(MYSQL *mysql, const char *stmt_str)
      if(mysql_query(connect_fd_,buf)!=0){
        printf("mysql_query error:%s\n",mysql_error(connect_fd_));
        mysql_close(connect_fd_);
        return false;
      }
      printf("sql语句成功执行！\n");
      //5.遍历结果集合
      //MYSQL_RES *mysql_store_result(MYSQL *mysql)
      MYSQL_RES* res=mysql_store_result(connect_fd_);
      if(res==NULL){
        printf("mysql store result error:%s\n",mysql_error(connect_fd_));
        mysql_close(connect_fd_);
        return false;
      }
      //6.获取行数
      //my_ulonglong mysql_num_rows(MYSQL_RES *result)
      int rows=mysql_num_rows(res);
      for(int i=0;i<rows;++i){
        //7.获取一行的数据
        //MYSQL_ROW mysql_fetch_row(MYSQL_RES *result)
        MYSQL_ROW arr=mysql_fetch_row(res);
        Json::Value val;
        val["tag_id"]=atoi(arr[0]);
        val["tag_name"]=arr[1];
        tag.append(val);
      }
      printf("共查到了%d条信息！\n",rows);
      //8.释放结果集合
      //void mysql_free_result(MYSQL_RES *result)
      mysql_free_result(res);
      return true;
    }
  private:
    MYSQL* connect_fd_;
};//end tag_table

