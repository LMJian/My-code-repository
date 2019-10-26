#include<stdio.h>
#include<pthread.h>
#include<inttypes.h>
#if 0
void* ThreadEntry(void* arg)
{
  (void)arg;
  while(1);

  return NULL;
}
int main()
{
  pthread_t tid1,tid2,tid3;
  pthread_create(&tid2,NULL,ThreadEntry,NULL);
  pthread_create(&tid1,NULL,ThreadEntry,NULL);
  pthread_create(&tid3,NULL,ThreadEntry,NULL);
  pthread_create(&tid3,NULL,ThreadEntry,NULL);
  pthread_create(&tid3,NULL,ThreadEntry,NULL);
  pthread_create(&tid3,NULL,ThreadEntry,NULL);
  pthread_create(&tid3,NULL,ThreadEntry,NULL);
  pthread_create(&tid3,NULL,ThreadEntry,NULL);
  pthread_create(&tid3,NULL,ThreadEntry,NULL);
  while(1)
  {

  }
  return 0;
}
#endif
#include<sys/time.h>

#define SIZE 100000000

int64_t GetUs(){
  struct timeval tv;
  gettimeofday(&tv,NULL);
  return tv.tv_sec*1000000+tv.tv_usec;
}
/*int64_t GetUs(){
  struct timeval tv;
  gettimeofday(&tv,NULL);
  return tv.tv_sec*1000000+tv.tv_usec;
}*/
void Calc(int* arr,int beg,int end)
{
  for(int i=beg;i<end;++i){
    arr[i]=arr[i]*arr[i];
  }
}
int main()
{
  srand(time(NULL));
  int *arr=(int*)malloc(sizeof(int)*SIZE);
  int64_t beg=GetUs();
  Calc(arr,0,SIZE);
  int64_t end=GetUs();
  printf("time =>%ld\n",end-beg);
  return 0;
}
