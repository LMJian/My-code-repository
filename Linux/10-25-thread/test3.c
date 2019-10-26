#include<stdio.h>
#include<unistd.h>
#include<pthread.h>
#include<inttypes.h>
#include<sys/time.h>
#include<stdlib.h>
#define THREAD_NUM 8

int64_t GetUs(){
  struct timeval tv;
  gettimeofday(&tv,NULL);
  return tv.tv_sec*1000000+tv.tv_usec;
}
void Calc(int* arr,int beg,int end)
{
  for(int i=beg;i<end;++i){
    arr[i]=arr[i]*arr[i];
  }
}
typedef struct Arg{
  int beg;
  int end;
  int* arr;
} Arg;
void* ThreadEntry(void* arg)
{
  Arg *p=(Arg*)arg;
  Calc(p->arr,p->beg,p->end);
  return NULL;
}
#define SIZE 100000000
int main()
{
  //int *arr=(int*)malloc(sizeof(int)*SIZE);
  int *arr=(int*)malloc(sizeof(int)*100000000);
  Arg args[THREAD_NUM];
  int base=0;
  for(int i=0;i<THREAD_NUM;++i){
    args[i].beg=base;
    args[i].end=base+SIZE/THREAD_NUM;
    args[i].arr=arr;
    base+=SIZE/THREAD_NUM;
  }
  pthread_t tid[THREAD_NUM];
  int64_t beg=GetUs();
  for(int i=0;i<THREAD_NUM;++i)
  {
    pthread_create(&tid[i],NULL,ThreadEntry,&args[i]);
  }

  for(int i=0;i<THREAD_NUM;++i){
    pthread_join(tid[i],NULL);
  }
  int64_t end=GetUs();

  printf("time=>%ld\n",end-beg);
  return 0;

}

