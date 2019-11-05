#include<stdio.h>
#include<unistd.h>
#include<pthread.h>
#include<thread>
#include<mutex>
#include<atomic>
#include<memory.h>

using namespace std;

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
};
pthread_rwlock_t lock;*/

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
    static mutex lock;
};
template<class T>
Singletion<T>::T* inst_=NULL;

int main()
{
  return 0;
}
