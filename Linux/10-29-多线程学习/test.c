#include<stdio.h>
#include<pthread.h>
#include<unistd.h>
#include<stdlib.h>
#include<signal.h>
#define THREAD_NUM 1

int g_count=0;
pthread_mutex_t mutex;
pthread_cond_t cond;

void ModifyCount(){
  pthread_mutex_lock(&mutex);
  ++g_count;
  printf("before sleep!\n");
  sleep(3);
  printf("after sleep!\n");
  pthread_mutex_unlock(&mutex);
}

void* ThreadEntry1(void *arg){
  (void)arg;
  /*for(int i=0;i<50000;++i){
    ModifyCount();
  }*/
  while(1){
    printf("传球！！\n");
    pthread_cond_signal(&cond);
    usleep(789789);
  }
  return NULL;
}
void* ThreadEntry2(void *arg){
  (void)arg;
  while(1){
    pthread_cond_wait(&cond,&mutex);
    printf("扣篮!!!\n");
    usleep(123456);
  }
  return NULL;
}
void MyHandler(int sig){
  (void)sig;
  ModifyCount();
}
int main(){
  pthread_mutex_init(&mutex,NULL);
  pthread_cond_init(&cond,NULL);
  pthread_t tid1,tid2;

  pthread_create(&tid1,NULL,ThreadEntry1,NULL);
  pthread_create(&tid2,NULL,ThreadEntry2,NULL);

  pthread_join(tid1,NULL);
  pthread_join(tid2,NULL);

  pthread_cond_destroy(&cond);
  //signal(SIGINT,MyHandler);
  
  /*pthread_t tid[THREAD_NUM];
  for(int i=0;i<THREAD_NUM;++i){
    pthread_create(&tid[i],NULL,ThreadEntry,NULL);
  }
  for(int i=0;i<THREAD_NUM;++i){
    pthread_join(tid[i],NULL);
  }
  printf("g_count=%d\n",g_count);*/
 
  pthread_mutex_destroy(&mutex);
  return 0;
}
