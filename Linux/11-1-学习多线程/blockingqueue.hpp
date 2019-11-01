#pragma once

#include<semaphore.h>
#include<vector>
#include<pthread.h>

template<class T>
class BlockingQueue{
  public:
    BlockingQueue(int max_size)
      :max_size_(max_size)
       ,head_(0)
       ,tail_(0)
       ,size_(0)
       ,queue_(max_size){
        sem_init(&lock_,0,1);


    }
    ~BlockingQueue()
    {
      sem_destroy(&lock_);
    }
    void Push(const T& data){
      sem_wait(&lock_);
      queue_[tail_]=data;
      ++tail_;
      ++size_;
      sem_post(&lock_);
    }
    void pop(T* data){
      sem_wait(&lock_);
      *data=queue_[head_];
      ++head_;
      --size_;
      sem_lock(&lock_);
    }
  private:
    std::vector<T> queue_; 
    int head_;
    int tail_;
    int size_;
    int max_size_;
    sem_t lock_;
};
int main()
{
  sem_init(&sem,0,2);
  

  sem_destroy(&sem);
  return 0;
}




