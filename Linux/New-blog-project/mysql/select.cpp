#include<stdio.h>
#include<stdlib.h>
#include<mysql/mysql.h>

int main(){
  //1.创建数据库连接句柄
  //MYSQL *mysql_init(MYSQL *mysql)
  MYSQL* connect_fd=mysql_init(NULL);
  if(connect_fd==NULL){
    printf("mysql init error:%s\n",mysql_error(connect_fd));
    mysql_close(connect_fd);
    return 1;
  }
  printf("句柄创建成功！\n");

  //2.和数据库建立连接
  //MYSQL *mysql_real_connect(MYSQL *mysql, const char *host, const char *user, const char *passwd, const char *db, unsigned int port, const char *unix_socket, unsigned long client_flag)
  if(mysql_real_connect(connect_fd, "127.0.0.1", "root", "LMJian521", "blog_db", 3306, NULL,1)==NULL){
    printf("mysql real connect error:%s\n",mysql_error(connect_fd));
    mysql_close(connect_fd);
    return 1;
  }
  printf("数据库连接成功！\n");

  //3.设置编码方式
  //mysql_set_character_set(MYSQL*,const char*)
  mysql_set_character_set(connect_fd,"utf8");

  //拼接sql语句
  char buf[1024]={0};
  sprintf(buf,"select * from blog_tb;");
  printf("sql:%s\n",buf);

  //4.让服务器执行sql语句
  //int mysql_query(MYSQL *mysql, const char *stmt_str)
  if(mysql_query(connect_fd,buf)!=0){
    printf("mysql_query error:%s\n",mysql_error(connect_fd));
    mysql_close(connect_fd);
    return 1;
  }
  printf("查找成功!\n");

  //5.遍历结果集合
  //MYSQL_RES *mysql_store_result(MYSQL *mysql)
  MYSQL_RES* res=mysql_store_result(connect_fd);
  if(res==NULL){
    printf("mysql store result error:%s\n",mysql_error(connect_fd));
    mysql_close(connect_fd);
    return 1;
  }
  //6.获取行数和列数
  //my_ulonglong mysql_num_rows(MYSQL_RES *result)
  //unsigned int mysql_num_fields(MYSQL_RES *result)
  size_t rows=mysql_num_rows(res);
  size_t fields=mysql_num_fields(res);
  for(size_t i=0;i<rows;++i){
    //7.获取一行的数据
    //MYSQL_ROW mysql_fetch_row(MYSQL_RES *result)
    MYSQL_ROW arr=mysql_fetch_row(res);
    for(size_t j=0;j<fields;++j){
      printf("%s\t",arr[j]);
    }
    printf("\n");
  }
  //8.释放结果集合
  //void mysql_free_result(MYSQL_RES *result)
  mysql_free_result(res); 
  
  //5.关闭数据库句柄
  //void mysql_close(MYSQL *mysql)
  mysql_close(connect_fd);
  return 0;
}
