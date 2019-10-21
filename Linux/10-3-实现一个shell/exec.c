#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/wait.h>
int main()
{
  int pid=fork();
  if(pid==0)
  {
    char* argv[]={"./mytest","mytest","-a",NULL};                                                                                                    
    char *env[]={"PATH=./TEST","HOME=~",NULL};
    printf("I am child!\n");
    //execl("./mytest","ls","-l","-a",NULL);
    //execlp("./mytest","mytest","-l",NULL);
    execve(argv[0],argv,env);
    perror("execl error");
    exit(0);
  }
  wait(NULL);
  printf("hello ~~bite~~!\n");
  return 0;
}
