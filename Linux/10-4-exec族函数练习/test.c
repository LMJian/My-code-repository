#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>

int main(int argc,char *argv[],char *env[])
{
  printf("lmj!!!!!!!!!!!!!!!!\n");
  int i;
  for(i=0;argv[i]!=NULL;i++)
  {
    printf("argv[%d]=[%s]\n",i,argv[i]);

  }
  for(i=0;env[i]!=NULL;i++)
  {
    printf("env[%d]=[%s]\n",i,env[i]);

  }
  return 0;
}
