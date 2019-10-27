#include<stdio.h>
#include<unistd.h>
#include<pthread.h>
#include<sys/syscall.h>
#include<stdlib.h>
void* test(void* arg)
{
  pthread_detach(pthread_self());
  (void)arg;
  //pid_t tid=syscall(SYS_gettid);
  int count=5;
  while(count--){
    //printf("test thread---pid=%d---tid=%d---_tid=%p\n",getpid(),tid,pthread_self());
    printf("test thread---\n");
    sleep(1);
  }
  int *p=(int*)malloc(sizeof(int));
  *p=5;
  //pthread_detach(pthread_self());
  return (void*)p;
}

int main()
{
  pthread_t tid;
  int ret=pthread_create(&tid,NULL,test,NULL);
  if(ret!=0){
    perror("pthread_create errno!!!\n");
    return -1;
  }
  //pthread_detach(pthread_self());
  int* p;
  p=(int*)malloc(sizeof(int));
  *p=4;
  ///pthread_cancel(tid);
  if(pthread_join(tid,(void**)&p)!=0)
    printf("errno\n");
  printf("main end---join return=%d\n",*p);
  /*int ttid=syscall(SYS_gettid);
  int count=0;
  while(1){
    if(count++==5)
      pthread_cancel(tid);
    printf("main thread---pid=%d---ttid=%d\npthread_self=%p---tid=%p\n",getpid(),ttid,pthread_self(),tid);
    sleep(1);
  }*/
  return 0;
}
