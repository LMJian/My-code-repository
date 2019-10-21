#include<stdio.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<unistd.h>
#include<string.h>

int main()
{
  const char *msg0="hello printf\n";
  const char *msg1="hello fwrite\n";
  const char *msg2="hello write\n";

  printf("%s",msg0);
  fwrite(msg1,strlen(msg0),1,stdout);
  write(1,msg2,strlen(msg2));
  fork();
  
  /*int fd=open("./log",O_CREAT|O_WRONLY,00644);
  if(fd<0)
  {
    perror("open");
    return 1;
  }
  close(1);
  dup2(fd,1);
  while(1)
  {
    char buf[1024]={0};
    ssize_t read_size=read(0,buf,sizeof(buf)-1);
    if(read_size<0)
    {
      perror("read");
      break;
    }
    printf("%s",buf);
    fflush(stdout);
  }

  /*close(1);

  int fd=open("myfile",O_WRONLY|O_CREAT,00644);
  if(fd<0)
  {
    perror("open");
    return 1;
  }
  printf("fd:%d\n",fd);
  fflush(stdout);
  close(fd);
  exit(0);
  /*char buf[1024]={0};
  ssize_t s=read(0,buf,sizeof(buf));
  if(s>0){
    buf[s]=0;
    write(1,buf,strlen(buf));
    write(2,buf,strlen(buf));
  }*/

  /*int fd=open("myfile",O_RDONLY);
  if(fd<0)
  {
    perror("open");
    return 1;
  }

  const char *msg="hello bit!\n";
  char buf[1024];
  while(1)
  {
    ssize_t s=read(fd,buf,strlen(msg));
    if(s>0)
    {
      printf("%s",buf);
    }
    else{
      break;
    }
  }
  close(fd);

  /*umask(0);
  int fd=open("myfile",O_WRONLY|O_CREAT,0644);
  if(fd<0)
  {
    perror("open");
    return 1;
  }
  int count=5;
  const char *msg="hello bit!\n";
  int len=strlen(msg);

  while(count--)
  {
    write(fd,msg,len);
  }
  close(fd);*/
  return 0;
}
