#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<pthread.h>

void *thread_run(void* arg)
{
  pthread_detach(pthread_self());
  printf("%s\n",(char*)arg);
  return NULL;
}
int main()
{
  pthread_t tid;
  pthread_create(&tid,NULL,thread_run,"runing...");

  int ret=0;
  sleep(1);
  if(pthread_join(tid,NULL)==0)
  {
    printf("wait success\n");
  }
  else{
    printf("wait failed\n");
    ret=1;
  }
  return ret;
}
