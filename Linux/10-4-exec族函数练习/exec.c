#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/wait.h>
int main()
{
  int pid=fork();
  if(pid==0)
  {
    char* argv[]={"./mytest","ls","-l","-a",NULL};                                                                                                    
    char *env[]={"PATH","HOME=~",NULL};
    printf("I am child!\n");


    //execlp("./mytest","-l",NULL);
    execle("mytest","-l","-a",NULL,env); 
    
    
    //execl("./mytest","ls","-l","-a",NULL);
    //execv(argv[0],argv+1);
    //execvp("./mytest",argv+1);
    //execve("./mytest",argv,env);
    perror("execl error");
    exit(0);
  }
  wait(NULL);
  printf("hello ~~bite~~!\n");
  return 0;
}
