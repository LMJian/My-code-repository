#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<errno.h>
#include<sys/stat.h>
#include<fcntl.h>
int main()
{
  char *fifo="./test.fifo";
  umask(0);
  int ret=mkfifo(fifo,0664);
  if(ret<0&&errno!=EEXIST)
  {
    perror("mkfifo error");
    return -1;
  }
  printf("prepare open fifo\n");
  int fd=open(fifo,O_RDONLY);
  if(fd<0)
  {
    perror("open error");
    return -1;
  }
  printf("open file sucess\n");
  while(1)
  {
    sleep(5);
    char buf[1024]={0};
    read(fd,buf,1023);
    printf("buf:[%s]\n",buf);
  }
  close(fd);
  return 0;
}

