#include<stdio.h>
#include<unistd.h>
#include<pthread.h>


void* ThreadEntry(void* ret)
{
  (void)ret;
  while(1){
    sleep(1);
    int *p=NULL;
    *p=10;
  }
  return NULL;
}


int main()
{
  pthread_t tid;
  pthread_create(&tid,NULL,ThreadEntry,NULL);
  while(1)
  {
    printf("In main Thread\n");
    sleep(1);
  }
  return 0;
}
