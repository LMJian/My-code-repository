//使用mysqlAPI实现数据的插入功能

#include<stdio.h>
#include<cstdlib>
//编译器默认从 /usr/include目录中查找头文件，mysql.h
#include<mysql/mysql.h>

int main(){
  //创建一个数据库连接句柄
  MYSQL* connect_fd=mysql_init(NULL);
  //和数据库建立连接（和tcp的区分开，这是应用层的）
  //连接过程需要指定一些必要的信息
  //     a)连接句柄
  //     b)服务器的ip地址
  //     c)用户名
  //     d)密码
  //     e)数据库名
  //     f)服务器的端口号
  //     g)unix_sock NULL;
  //     h)client_flag 0
  if(mysql_real_connect(connect_fd,"127.0.0.1","root","lmj521","blog_system2",3306,NULL,0)==NULL){
    printf("链接失败！%s\n",mysql_error(connect_fd));
    return 1;
  }
  printf("链接成功！\n");
  //断开连接
  mysql_close(connect_fd);

  return 0;
}
