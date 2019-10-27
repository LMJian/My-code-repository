#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<pthread.h>

void *thread_run(void* arg){
  sleep(1);
  pthread_detach(pthread_self());
  printf("%s\n",(char*)arg);
  //sleep(5);
  int *p=(int*)malloc(sizeof(int));
  *p=4;
  return (void*)p;
}
int main(){
  pthread_t tid;
  if(pthread_create(&tid,NULL,thread_run,"thread1 run...")!=0){
    printf("create thread error\n");
    return 1;
  }
  int ret=0;
  //sleep(1);
  int *p=(int*)malloc(sizeof(int));
  *p=5;
  
  if(pthread_join(tid,(void**)&p)==0){
    printf("pthread wait success\n");
    ret=0;
  }
  else{
    printf("pthread wait failed\n");
    ret=1;
  }
  printf("*p=%d\n",*p);
  return ret;
}
