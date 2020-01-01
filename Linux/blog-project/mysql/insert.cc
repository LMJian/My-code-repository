//使用mysqlAPI实现数据的插入功能
#include<stdio.h>
#include<cstdlib>
//编译器默认从 /usr/include目录中查找头文件，mysql.h
#include<mysql/mysql.h>

int main(){
  //1.创建一个数据库连接句柄
  //如果传的是一个空指针，函数将返回一个新对象
  MYSQL* connect_fd=mysql_init(NULL);
  //2.和数据库建立连接（和tcp的区分开，这是应用层的）
  //MYSQL *mysql_real_connect(MYSQL *mysql, const char *host, const char *user, const char *passwd, const char *db, unsigned int port, const char *unix_socket, unsigned long client_flag)
  //连接过程需要指定一些必要的信息
  //     a)连接句柄
  //     b)服务器的ip地址
  //     c)用户名
  //     d)密码
  //     e)数据库名
  //     f)服务器的端口号
  //     g)unix_sock NULL;
  //     h)client_flag 0
  if(mysql_real_connect(connect_fd,"127.0.0.1","root","","blog_system2",3306,NULL,0)==NULL){
    printf("链接失败！%s\n",mysql_error(connect_fd));
    return 1;
  }
  printf("链接成功！\n");
  //3.设置编码方式  我这里默认设置为utf8
  mysql_set_character_set(connect_fd,"utf8");
  //拼接sql语句
  char sql[1024*4]={0};
  char title[]="立一个flag";
  char content[]="我要拿成为大佬";
  int tag_id=1;
  char date[]="2019/07/25";
  sprintf(sql,"insert into blog_table values(null,'%s','%s',%d,'%s')",title,content,tag_id,date);
  printf("sql:%s\n",sql);
  //让服务器执行sql
  int ret=mysql_query(connect_fd,sql);
  if(ret<0){
    printf("执行SQL失败!%s\n",mysql_error(connect_fd));
    mysql_close(connect_fd);
    return 1;
  }
  printf("插入成功!\n");
  //断开连接
  mysql_close(connect_fd);
  return 0;
}
