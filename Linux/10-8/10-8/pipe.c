#include<stdio.h>
#include<unistd.h>
#include<errno.h>
#include<stdlib.h>
#include<string.h>
#include<wait.h>
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
    printf("pid=%d\n",getpid());
    close(pipefd[1]);
    close(pipefd[0]);
    printf("child\n");
    char buf[1024]={0};
    int ret;
    ret=read(pipefd[0],buf,1023);
    printf("buf:%d-%s\n",ret,buf);
    buf[0]='\0';
    ret=read(pipefd[0],buf,1023);
    printf("buf:%d-%s\n",ret,buf);
    close(pipefd[0]);
  }
  else{
    close(pipefd[0]);//不关闭此，父进程会提前结束
    printf("father\n");
    char *ptr="爱玉玉爱生活~~~";
    int ret;
    ret=  write(pipefd[1],ptr,strlen(ptr));
    printf("ret:%d\n",ret);
    close(pipefd[1]);
  }
  printf("end\n");
  return 0;
}
