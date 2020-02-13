#include<stdio.h>
#include<unistd.h>
#include<pthread.h>

void* start(void* arg){
  (void)arg;
  for(int i=0;i<20;++i){
    printf("son %d\n",i);
    usleep(200);
  }
  return NULL;
}
int main(){
  pthread_t pid;
  pthread_create(&pid,NULL,start,NULL);
  for(int i=0;i<20;++i){
    printf("father %d\n",i);
    usleep(500);
  }
  pthread_join(pid,NULL);
  return 0;
}
