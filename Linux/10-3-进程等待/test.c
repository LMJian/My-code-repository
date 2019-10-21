#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<string.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<errno.h>
int main()
{
  pid_t ret=fork();
  if(ret>0)
  {
    printf("this is test for wait\n");
    int status=0;
    pid_t result=wait(&status);
    printf("result %d,status %d\n",result,status);
    if(status&0xff)
      printf("异常终止%d\n",status&0x7f);
    else{
      printf("正常终止：%d\n",(status>>8)&0xff);
    }
  }
  else if(ret==0)
  {
    printf("child is run,pid is :%d\n",getpid());
    sleep(5);
    exit(257);
  }
  else{
    printf("fork error\n");
    return 1;
  }
  /*pid_t pid;
  if((pid=fork())==-1)
    perror("fork"),exit(1);
  if(pid==0)//子进程
  {
    printf("child %d\n",getpid());
    sleep(20);
    exit(10);
  }
  else{//父进程
    int st;
    int ret=wait(&st);
    if(ret>0&&(st&0x7f)==0)
    {
      printf("ret:%d,st:%d\n",ret,st);
      printf("child exit code :%d\n",(st>>8)&0xff);
    }
    else if(ret>0)//异常
    {
      printf("ret:%d,st:%d\n",ret,st);
      printf("sig code :%d\n",st&0x7f);
    } 
  }*/
}
