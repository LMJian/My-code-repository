#include<iostream>
#include<queue>
#include<stdlib.h>
#include<pthread.h>

#define NUM 8

class BlockQueue{
  private:
    std::queue<int> q;
    int cap;
    pthread_mutex_t lock;
    pthread_cond_t full;
    pthread_cond_t empty;

  private:
    void LockQueue()
    {
      pthread_mutex_lock(&lock);
    }
    void UnLockQueue()
    {
      pthread_mutex_unlock(&lock);
    }
    void ProductWait()
    {
      pthread_cond_wait(&full,&lock);
    }
    void ConsumeWait()
    {
      pthread_cond_wait(&empty,&lock);
    }
    void NotifyProduct()
    {
      pthread_cond_signal(&full);
    }
    void NotifyConsume()
    {
      pthread_cond_signal(&empty);
    }
    bool IsEmpty()
    {
      return (q.size()==0?true:false);
    }
    bool IsFull()
    {
      return (q.size()==cap?true:false);
    }
  public:
    BlockQueue(int _cap=NUM)
      :cap(_cap)
    {
      pthread_mutex_init(&lock,NULL);
      pthread_cond_init(&full,NULL);
      pthread_cond_init(&empty,NULL);
    }
    void PushData(const int &data)
    {
      LockQueue();//lock上锁
      while(IsFull()){//判满
        NotifyConsume();//同步操作，通知empty
        std::cout<<"queue full,notify consume data,product stop."<<std::endl;
        ProductWait();//同步操作，等待full(等待pop操作)
      }
      q.push(data);
      NotifyConsume();//同步操作，通知empty(通知进行了push操作)
      UnLockQueue();//lock解锁
    }
    void PopData(int &data)
    {
      LockQueue();//lock上锁
      while(IsEmpty())//判空
      {
        NotifyProduct();//同步操作，通知full
        std::cout<<"queue empty.notify product data,consume stop."<<std::endl;
        ConsumeWait();//同步操作,等待empty(等待push操作)
      }
      data=q.front();
      q.pop();
      NotifyProduct();//同步操作，通知full(通知进行了pop操作)
      UnLockQueue();//lock解锁
    }
    ~BlockQueue()
    {
      pthread_mutex_destroy(&lock);
      pthread_cond_destroy(&full);
      pthread_cond_destroy(&empty);
    }
};
void *consumer(void* arg)
{
  BlockQueue *bqp=(BlockQueue*)arg;
  int data;
  while(1)
  {
    bqp->PopData(data);
    std::cout<<"Consume data done:"<<data<<std::endl;
  }
}
void *producter(void* arg)
{
  BlockQueue *bqp=(BlockQueue*)arg;
  srand((unsigned long)time(NULL));
  while(1){
    int data=rand()%1024;
    bqp->PushData(data);
    std::cout<<"Prodoct data done:"<<data<<std::endl;
  }
}

int main()
{
  BlockQueue bq;
  pthread_t c,p;
  pthread_create(&c,NULL,consumer,(void*)&bq);
  pthread_create(&p,NULL,producter,(void*)&bq);

  pthread_join(c,NULL);
  pthread_join(p,NULL);

  return 0;
}
