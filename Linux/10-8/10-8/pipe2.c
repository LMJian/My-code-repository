#include <stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<errno.h>
#include<sys/wait.h>
int main()
{
  int pipefd[2];
  if(pipe(pipefd)<0)
  {
    perror("pipe error");
    return -1;
  }
  int pid1=fork();
  if(pid1==0)
  {
    printf("write:%d\n",getpid());
    close(pipefd[0]);
    dup2(pipefd[1],1);
    execlp("ls","ls",NULL);
    exit(-1);
  }
  int pid2=fork();
  if(pid2==0)
  {
    printf("read:%d\n",getpid());
    close(pipefd[1]);
    dup2(pipefd[0],0); 
    execlp("grep","grep","make",NULL);
    exit(-1);
  }
  printf("father:%d\n",getpid());
  close(pipefd[0]);
  close(pipefd[1]);


  wait(NULL);
  wait(NULL);
  return 0;
}
