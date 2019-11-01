#include<stdio.h>
#include<unistd.h>
#include<pthread.h>
#include<vector>
#include<queue>
using namespace std;

std::vector<int> data;
pthread_mutex_t lock;
pthread_cond_t cond;


void* Product(void *arg)
{
  (void)arg;
  int count=0;
  while(1)
  {
    pthread_mutex_lock(&lock);
    data.push_back(++count);
    pthread_mutex_unlock(&lock);
    pthread_cond_signal(&cond);
    usleep(789789);
  }
  return NULL;
}
void* Consume(void *arg)
{
  (void)arg;
  while(1)
  {
    pthread_mutex_lock(&lock);
    if(data.empty())
    {
      pthread_cond_wait(&cond,&lock);
    }
    printf("result=%d\n",data.back());
    data.pop_back(); 
    pthread_mutex_unlock(&lock);
    usleep(123123);
  }
  return NULL;
}
int main()
{
  pthread_mutex_init(&lock,NULL);
  pthread_cond_init(&cond,NULL);
  pthread_t tid1,tid2,tid3,tid4;
  pthread_create(&tid1,NULL,Product,NULL);
  pthread_create(&tid3,NULL,Product,NULL);
  pthread_create(&tid2,NULL,Consume,NULL);
  pthread_create(&tid4,NULL,Consume,NULL);
  pthread_join(tid1,NULL);
  pthread_join(tid2,NULL);
  pthread_join(tid3,NULL);
  pthread_join(tid4,NULL);

  pthread_mutex_destroy(&lock);
  pthread_cond_destroy(&cond);



  return 0;
}
