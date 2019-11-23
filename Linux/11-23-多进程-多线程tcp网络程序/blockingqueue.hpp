#pragma once

#include<iostream>
#include<semaphore.h>
#include<vector>
using namespace std;

//阻塞队列
template<class T>
class BlockingQueue
{
  public:
    BlockingQueue(int maxsize=100)
      :_queue(maxsize)
       ,_head(0)
       ,_tail(0)
       ,_size(0)
       ,_maxsize(maxsize)
    {
      sem_init(&_lock,0,1);
      sem_init(&_used,0,0);
      sem_init(&_rem,0,maxsize);
    }
    ~BlockingQueue()
    {
      sem_destroy(&_lock);
      sem_destroy(&_used);
      sem_destroy(&_rem);
    }
    void Push(const T& data)
    {
      sem_wait(&_rem);
      sem_wait(&_lock);
      _queue[_tail]=data;
      _tail=(_tail+1)%_maxsize;
      ++_size;
      sem_post(&_lock);
      sem_post(&_used);
    }
    void Pop(T& data)
    {
      sem_wait(&_used);
      sem_wait(&_lock);
      data=_queue[_head];
      _head=(_head+1)%_maxsize;
      --_size;
      sem_post(&_lock);
      sem_post(&_rem);
    }
  private:
    int _head;
    int _tail;
    int _size;
    int _maxsize;
    vector<T> _queue;
    sem_t _lock;//互斥锁
    sem_t _used;//已使用
    sem_t _rem;//未使用
};
