#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/wait.h>

int main()
{
  pid_t ret1=fork();
  if(ret1==0)
  {
    printf("child1 %d\n",getpid());
    sleep(5);
    exit(0);
  }
  pid_t ret2=fork();
  if(ret2==0)
  {
    printf("child2 %d\n",getpid());
    exit(0);
  }
  printf("father %d\n",getpid());
  int ret=0;
  int count=0;
  while(1)
  {
    ret=waitpid(-1,NULL,WNOHANG);
    printf("wait1 %d\n",ret);
    if(ret>0)
    {
      break;
    }
    ++count;
  }
  printf("count %d\n",count);
  ret=waitpid(ret2,NULL,0);
  printf("wait2 %d\n",ret);
  while(1)
  {
    sleep(1);
  }
   return 0;
}
