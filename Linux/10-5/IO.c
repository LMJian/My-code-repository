#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<fcntl.h>

int main()
{
  int fd;
  char *file="./tmp.txt";
  umask(0);
  fd=open(file,O_RDWR|O_CREAT,0664);
  if(fd<0)
  {
    perror("open error");
    return -1;
  }
  lseek(fd,10,SEEK_END);
  char buf[1024]="ruhehuodao~~99?\n";
  int ret=write(fd,buf,strlen(buf));
  if(ret<0)
  {
    perror("write error");
  }
  lseek(fd,0,SEEK_SET);


  memset(buf,0x00,1024);
  ret=read(fd,buf,1023);
  if(ret<0)
  {
    perror("read error");
    return -1;
  }
  else if(ret==0)
  {
    printf("have no data\n");
    return -1;
  }
  printf("buf:[%d-%s]\n",ret,buf);

  close(fd);
  return 0;
}
