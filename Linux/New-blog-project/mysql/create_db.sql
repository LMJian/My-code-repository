drop database if exists blog_db;
create database blog_db;
use blog_db;

drop table if exists blog_tb;
create table blog_tb(
  blog_id int not null primary key auto_increment,
  title varchar(40) not null,
  content text,
  create_time timestamp,
  tag_id int
);

drop table if exists tag_tb;
create table tag_tb(
  tag_id int not null primary key auto_increment,
  tag_name varchar(30) not null
);

