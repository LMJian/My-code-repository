#include<stdio.h>
#include<unistd.h>
#include<string.h>
#include<stdlib.h>
#include<fcntl.h>
#include<sys/types.h>
#include<sys/stat.h>

char str[100]={0};
char *maze[100]={0};
int len=0;

void do_str()
{
  char *ptr=str;
  while(*ptr!='\0')
  {
    if(*ptr!=' ')
    {
      maze[len++]=ptr;
      while(*ptr!=' '&&*ptr!='\0')
        ptr++;
      *ptr='\0';
    }
    ptr++;
  }
  maze[len]=NULL;
}
void do_exec()
{
  for(int i=0;i<len;i++)
  {
    if(strcmp(maze[i],"|")==0)
    {
      maze[i]=NULL;
      int pd=fork();
      if(pd<0)
      {
        perror("fork errno");
        exit(-1);
      }
      if(pd==0)
      {
        int fd=open("tmp.txt",O_WRONLY|O_CREAT,0664);
        dup2(fd,1);
        execvp(maze[0],maze);
        perror("write errno");
      }
      wait(NULL);
      pd=fork();
      if(pd<0)
      {
        perror("fork errno");
        exit(-1);
      }
      if(pd==0)
      {
        int fd=open("tmp.txt",O_RDONLY);
        dup2(fd,0);
        execvp(maze[i+1],maze+i+1);
        perror("read errno");
        exit(-1);
      }
      wait(NULL);
      break;
  }
}
}
int main()
{
  gets(str);
  do_str();
  do_exec();
  return 0;
}
