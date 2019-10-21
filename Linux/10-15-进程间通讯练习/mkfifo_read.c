#include<unistd.h>
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<errno.h>
#include<fcntl.h>
#include<sys/types.h>

int main()
{
  int mk=mkfifo("p2",0664);
  if(mk<0)
  {
    //perror("mkfifo errno");
    //exit(-1);
  }
  int fd=open("a.txt",O_RDONLY); 
  if(fd<0)
  {
    perror("open a.txt errno");
    exit(-1);
  }
  int mkfd=open("p2",O_RDWR);
  if(mkfd<0)
  {
    perror("open p2 errno");
    exit(-1);
  }
  int buf[100]={0};
  while(read(fd,buf,2)>0)
  {
    write(mkfd,buf,strlen(buf));
  }
  close(mk);
  close(fd);
  return 0;
}
