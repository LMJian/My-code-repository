drop database blog_system2;
create database blog_system2;
use blog_system2;

drop table if exists blog_table;
create table blog_table(
  blog_id int not null primary key auto_increment,
  title varchar(50),
  content text,
  tag_id int,
  create_time varchar(50)
);

drop table if exists tag_table;
create table tag_table(
  tag_id int not null primary key auto_increment,
  tag_name varchar(50)
);
