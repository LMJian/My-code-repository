#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/wait.h>
#include<string.h>
int Split(char input[],char* output[])
{
    char *p=strtok(input," ");
    int i=0;
    while(p!=NULL)
    {
      //printf("%s\n",p);
      output[i++]=p;

      p=strtok(NULL," ");
    }
    return i;
}
int main()
{
  while(1){
    printf("[myshell@localhost ~]$ ");
    fflush(stdout);

    char command[1024]={0};
    gets(command);
    char *argv[1024]={0};
    int n=Split(command,argv);
    CreateProcess();
    


  }
  
  return 0;
}

