#include<stdio.h>
#include<unistd.h>
#include<pthread.h>


void* ThreadEntry(void* arg)
{
  int *p=(int*)arg;
  (void) arg;

  while(1)
  {
    printf("In ThreadEntry\n");
    sleep(1);
    ++*p;
  }
  return NULL;
}
int main()
{
  int *p=(int*)malloc(4);
  *p=0;
  pthread_t tid;
  int ret=pthread_create(&tid,NULL,ThreadEntry,p);
  if(ret!=0)
  {
    perror("create errno\n");
    return -1;
  }
  pthread_detach(tid);
  while(1)
  {  
    printf("In main Thread %d\n",*p);
    sleep(1);
  }
  //pthread_cancel(tid);
  //pthread_join(tid,NULL);
  //printf("new thread end\n");
  return 0;
}
