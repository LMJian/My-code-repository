#include<stdio.h>
#include<unistd.h>
#include<string.h>
#include<stdlib.h>
#include<fcntl.h>

char command[1024]={0};

int input()
{
  printf("[user@myshell]$ ");
  fflush(stdout);
  memset(command,0,1024);
  gets(command);
  if(command[0]=='\0')
  {
    return -1;
  }
  return 0;
}

void do_exec()
{
  char *arr[32]={0};
  char *ptr=command;
  int len=0;
  while(*ptr!='\0')
  {
    if(!isspace(*ptr))
    {
      arr[len++]=ptr;
      while((!isspace(*ptr))&&(*ptr!='\0'))
      {
        ptr++;
      }
      *ptr='\0';
    }
    ptr++;
  }
  arr[len]=NULL;
  if(strcmp(arr[0],"cd")==0)
  {
    chdir(arr[1]);
    return;
  }
  
  pid_t id=fork();
  if(id==0)
  {
    int i;
    int fd=1;
    for(i=0;i<len;i++)
    {
      if(strcmp(arr[i],">")==0)
      {
        fd=open(arr[i+1],O_WRONLY|O_CREAT|O_TRUNC,0664);
        dup2(fd,1);
        arr[i]=NULL;
        break;
      }else if(strcmp(arr[i],">>")==0)
      {
        fd=open(arr[i+1],O_WRONLY|O_CREAT|O_APPEND,0664);
        dup2(fd,1);
        arr[i]=NULL;
        break;
      }
    }
    execvp(arr[0],arr);
    exit(-1);
  }
  wait(NULL);
}

int main()
{
  while(1)
  {
    if(input()<0)
      continue;
    do_exec();
  }
  return 0;
}
