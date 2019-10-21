#include<unistd.h>
#include<stdlib.h>
#include<stdio.h>
#include<errno.h>
#include<string.h>

#define ERR_EXIT(m)     (perror(m),exit(EXIT_FAILURE))

int main()
{
  int pipefd[2];
  if(pipe(pipefd)==-1)
    ERR_EXIT("pipe error");
  pid_t pid;
  pid=fork();
  if(pid==-1)
    ERR_EXIT("fork error");

  if(pid==0)
  {
    close(pipefd[0]);
    write(pipefd[1],"hello",5);
    //close(pipefd[1]);
    exit(EXIT_SUCCESS);
  }

  close(pipefd[1]);
  char buf[10]={0};
  read(pipefd[0],buf,10);
  printf("buf=%s\n",buf);
  return 0;
}
