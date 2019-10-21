#include<stdio.h>
#include<unistd.h>
#include<errno.h>
#include<stdlib.h>
#include<string.h>
int main()
{
  int pipefd[2];
  int ret=pipe(pipefd);
  if(ret<0)
  {
    perror("pipe error");
    return -1;
  }
  int pid=fork();
  if(pid<0)
  {
    perror("fork error");
    exit(-1);
  }
  else if(pid==0)
  {
    printf("child:%d\n",pipefd[0]);
    sleep(1);
    close(pipefd[1]);
    char buf[1024]={0};
    int ret=read(pipefd[0],buf,1023);
    printf("buf:%d-%s\n",ret,buf);

    ret=read(pipefd[0],buf,1023);
    printf("buf:%d-%s\n",ret,buf);
  }
  else{
    printf("father:%d\n",pipefd[0]);
    char *ptr="爱玉玉爱生活~~~";
    //write(pipefd[1],ptr,strlen(ptr));
    close(pipefd[1]);
    sleep(1000);
    //sleep(1000);
  }
  //printf("------------exit\n");
  return 0;
}
