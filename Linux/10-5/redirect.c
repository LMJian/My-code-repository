#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<fcntl.h>

int main()
{
  close(1);

  int fd=open("./tmp.txt",O_RDWR|O_CREAT,0664);
  if(fd<0)
  {
    perror("open error");
    return -1;
  }
  //dup2(fd,1);
  printf("fd:%d\n",fd);
  fflush(stdout);
  close(fd);
  return 0;
}
