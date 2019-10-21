#include<stdio.h>
#include<unistd.h>
#include<errno.h>
#include<string.h>
#include<stdlib.h>

int main()
{
  while(1)
  {
    char buf[1024]={0};
    printf("[user@localhost]$ ");
    fflush(stdout);
    if(scanf("%[^\n]%*c",buf)!=1)
    {
      getchar();
      continue;
    }
    //printf("buf:[%s]\n",buf);
    
    int argc=0;
    char *argv[32];
    char *ptr=buf;
    while(*ptr!='\0')
    {
      if(!isspace(*ptr))
      {
        argv[argc]=ptr;
        argc++;
        while(!isspace(*ptr)&&*ptr!='\0')
        {
          ptr++;
        }
        *ptr='\0';
       // printf("argv[%d]=[%s]\n",argc,argv[argc-1]);
      }
      ptr++;
    }
    argv[argc]=NULL;
    if(strcmp(argv[0],"cd")==0)
    {
      chdir(argv[1]);
      continue;
    }
    int  pid=fork();
    if(pid<0)
    {
      perror("fork error");
      return -1;
    }
    else if(pid==0)
    {
      execvp(argv[0],argv);
      exit(-1);
    }
    wait(NULL);
  }
  return 0;
}
