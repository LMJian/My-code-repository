#include<unistd.h>
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<errno.h>
#include<fcntl.h>
#include<sys/types.h>

int main()
{
  int fd=open("b.txt",O_WRONLY|O_CREAT,0664);
  if(fd<0)
  {
    perror("open b.txt errno");
    exit(-1);
  }
  int mkfd=open("p2",O_RDONLY);
  if(mkfd<0)
  {
    perror("open p2 errno");
    exit(-1);
  }
  int buf[100]={0};
  while(read(mkfd,buf,2)>0)
  {
    write(fd,buf,strlen(buf));
  }
  close(fd);
  close(mkfd);
  unlink("p2");
  return 0;
}
