#include<stdio.h>
#include<unistd.h>
#include<pthread.h>
#include<vector>
#include"blockingqueue.hpp"
using namespace std;

#if 0
pthread_mutex_t lock;
pthread_cond_t cond;
BlockingQueue<int> queue(100);
vector<int> data;


void* Product(void *arg)
{
  (void)arg;
  int count=0;
  while(1)
  {
    queue.Push(++count);
    usleep(789789);
  }
  /*int count=0;
  while(1)
  {
    pthread_mutex_lock(&lock);
    data.push_back(++count);
    pthread_mutex_unlock(&lock);
    pthread_cond_signal(&cond);
    usleep(789789);
  }*/
  return NULL;
}
void* Consume(void *arg)
{
  (void)arg;
  /*while(1)
  {
    int count=0;
    queue.Pop(&count);
    printf("count=%d\n",count);
    usleep(123123);
  }*/
  while(1)
  {
    pthread_mutex_lock(&lock);
    while(data.empty())
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
  /*pthread_t tid1,tid2;
  pthread_create(&tid1,NULL,Product,NULL);
  pthread_create(&tid2,NULL,Consume,NULL);


  pthread_join(tid1,NULL);
  pthread_join(tid2,NULL);*/
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
#endif

#include"threadpool.hpp"
#include<pthread.h>
#include<sys/types.h>
#include<sys/syscall.h>

class MyTask:public Task{
  public:
    MyTask(int id)
      :id_(id)
    {

    }
    virtual ~MyTask()
    {

    }
    void Run(){

      printf("tid=%d,id=%d\n",syscall(SYS_gettid),id_);
    }
  private:
    int id_;

};
int test()
{
  ThreadPool pool(10);
  for(int i=0;i<20;++i)
  {
    pool.AddTask(new MyTask(i));
  }
  while(1)
    sleep(1);
  return 0;

}
int main()
{
  test();
  return 0;
}
