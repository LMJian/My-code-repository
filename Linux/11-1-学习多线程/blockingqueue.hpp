#pragma once

#include<semaphore.h>
#include<vector>
#include<pthread.h>

//阻塞队列
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
        sem_init(&elem_,0,0);
        sem_init(&blank_,0,max_size);
    }
    ~BlockingQueue()
    {
      sem_destroy(&lock_);
      sem_destroy(&elem_);
      sem_destroy(&blank_);
    }
    void Push(const T& data){
      sem_wait(&blank_);
      sem_wait(&lock_);
      queue_[tail_]=data;
      ++tail_;
      ++size_;
      sem_post(&lock_);
      sem_post(&elem_);
    }
    void Pop(T* data){
      sem_wait(&elem_);
      sem_wait(&lock_);
      *data=queue_[head_];
      ++head_;
      --size_;
      sem_post(&lock_);
      sem_post(&blank_);
    }
  private:
    std::vector<T> queue_; 
    int head_;
    int tail_;
    int size_;
    int max_size_;
    sem_t lock_;//互斥锁
    sem_t elem_;//已用资源数
    sem_t blank_;//可用资源数
};
