#include<stdio.h>
#include<unistd.h>
#include<pthread.h>
#include<thread>
#include<mutex>
#include<atomic>
#include<memory.h>

using namespace std;

#if 0
/*pthread_rwlock_t lock;
int count=0;
void* Reader(void* arg)
{
  (void)arg;
  while(1)
  {
    pthread_rwlock_rdlock(&lock);
    printf("count==%d\n",count);
    pthread_rwlock_unlock(&lock);
    sleep(1);
  }
  return NULL;
}
void* Writer(void* arg)
{
  (void)arg;
  int _count=0;
  while(1)
  {
    pthread_rwlock_wrlock(&lock);
    ++_count;
    count=_count;
    pthread_rwlock_unlock(&lock);
    sleep(1);
  }
  return NULL;
}*/
atomic_int count(0);
mutex lock;
void Handler(shared_ptr<int> p)
{
  shared_ptr<int> p3(p);

  /*for(int i=0;i<50000;++i)
  {
    ++count;
  }*/
  /*while(1)
  {
    lock.lock();
    printf("hehe=%d,%s\n",num,id.c_str());
    lock.unlock();
    sleep(1);
  }*/
}

int main()
{

  shared_ptr<int> p1(new int[10]);
  shared_ptr<int> p2(p1);

  thread t1(Handler,p1);
  thread t2(Handler,p2);

  /*thread t1(Handler);
  thread t2(Handler);
  t1.join();
  t2.join();
  printf("count=%d\n",(int)count);*/
  
  /*pthread_rwlock_init(&lock,NULL);
  pthread_t tid1,tid2,tid3,tid4;
  pthread_create(&tid1,NULL,Reader,NULL);
  pthread_create(&tid3,NULL,Reader,NULL);
  pthread_create(&tid4,NULL,Reader,NULL);
  pthread_create(&tid2,NULL,Writer,NULL);

  pthread_join(tid1,NULL);
  pthread_join(tid2,NULL);
  pthread_rwlock_destroy(&lock);*/
  return 0;
}
#endif


//饿汉模式
/*template<class T>
class Singletion{
  public:
    static T* Instance()
    {
      return &inst_;
    }
  private:
    static T inst_;
};*/
pthread_rwlock_t lock;

//懒汉模式
template<class T>
class Singletion{
  public:
    static T* Instance()
    {
      if(inst_==NULL)
      {
       lock.lock();
       if(inst_==NULL)
       {
         inst_=new T();
        }
       lock.unlock();
      }
      return inst_;
    }
  private:
    volatile static T* inst_=NULL;
};


make_pair;//工厂模式
make_heap;//


