#include<stdio.h>
#include<unistd.h>
#include<pthread.h>

void *thr_start(void *arg)
{
  while(1){
    printf("i am normal thread---ptr:%s\n",(char*)arg);
    sleep(1);
  }
  return NULL;
}
int main()
{
  pthread_t tid;
  int ret;
  char *ptr="leihoua~~~~";
  ret=pthread_create(&tid,NULL,thr_start,(void*)ptr);
  if(ret!=0){
    printf("thread create error\n");
    return -1;
  }    
  while(1){
    printf("i am main thread----new thread id:%p\n",tid);
    sleep(1);
  }


  return 0;
}
