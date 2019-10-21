#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<errno.h>
#include<string.h>
#include<fcntl.h>
#include<sys/stat.h>

#define ERR_EXIT(m)   (perror(m),exit(EXIT_FAILURE))

int main()
{
  int outfd;
  outfd=open("abc.bak",O_WRONLY|O_CREAT|O_TRUNC,0644);
  if(outfd==-1)
    ERR_EXIT("open");
  int infd;
  infd=open("tp",O_RDONLY);
  if(infd==-1)
    ERR_EXIT("open");

  char buf[1024];
  int n;
  while((n=read(infd,buf,1024))>0)
  {
    write(outfd,buf,n);
  }
  close(infd);
  close(outfd);
  unlink("tp");
  return 0;
}
