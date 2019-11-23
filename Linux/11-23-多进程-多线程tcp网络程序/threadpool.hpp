#pragma once

#include"blockingqueue.hpp"

class Stack
{
public:
  Stack(void *arg)
    :_arg(arg)
  {}
  virtual void Entry(){

  }
  ~Stack()
  {}
  void* _arg;
};

//线程池
class ThreadPool
{
public:
  ThreadPool(int thread_size,int queue_size=100)
  :_queue(queue_size)
   ,_size(thread_size)
  {
    for(int i=0;i<_size;++i)
    {
      pthread_t tid;
      pthread_create(&tid,NULL,PthreadEntry,this);
      tid_arr.push_back(tid);
    }
  }
  ~ThreadPool()
  {
    for(int i=0;i<_size;++i)
    {
      pthread_cancel(tid_arr[i]);
    }
    for(int i=0;i<_size;++i)
    {
      pthread_join(tid_arr[i],NULL);
    }
  }
  void AddStack(Stack* ptr)
  {
    _queue.Push(ptr);
  }
private:
  BlockingQueue<Stack*> _queue;
  int _size;
  vector<pthread_t> tid_arr;

  static void* PthreadEntry(void* arg)
  {
    ThreadPool* ptr=(ThreadPool*)arg;
    while(1)
    {
      Stack* pst=NULL;
      ptr->_queue.Pop(pst);
      pst->Entry();
    }
  }
};
