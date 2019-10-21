#include<stdio.h>
#include<unistd.h>
#include<signal.h>

int main()
{
  raise(SIGQUIT);

  /*alarm(3);
  sleep(1);
  int ret=alarm(0);
  printf("%d\n",ret);
  /*abort();
  raise(3);
  kill(getpid(),3);*/
  while(1)
  {
    printf("hehe\n");
    sleep(1);
  }
  return 0;
}
