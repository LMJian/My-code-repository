#include<unistd.h>
#include<stdio.h>
#include<string.h>
#include<stdlib.h>

int main()
{
  int fd[2];
  if(pipe(fd)<0)
  {
    perror("pipe error");
    return -1;
  }
  int ret=fork();
  if(ret<0)
  {
    perror("fork error");
    return -1;
  }
  if(ret==0)
  {
    close(fd[0]);
    char buf[10];
    fgets(buf,100,stdin);
    int len=strlen(buf);
    if(write(fd[1],buf,len)!=len)
    {
      perror("write error");
      return -1;
    }
    close(fd[1]);
    return 0;
  }
  close(fd[1]);
  int buf[100];
  if(read(fd[0],buf,100)==-1)
  {
    perror("read error");
    return -1;
  }
  //printf("%s\n",buf);
  int len=strlen(buf);
  if(write(1,buf,len)!=len)
  {
    perror("printf error");
    return -1;
  }
  return 0;
}
