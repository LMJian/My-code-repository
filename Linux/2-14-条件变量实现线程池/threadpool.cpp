#include<iostream>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<queue>

class Start{
  public:
    Start(int id)
      :id_(id)
    {}
    virtual void Run(){
      printf("Start is running!!!\n");
    }
    int id_;
};

class ThreadPool{
  public:
    ThreadPool(int threadSize)
    :threadSize_(threadSize)
    {
      pthread_mutex_init(&mutex_,NULL);
      pthread_cond_init(&cond_,NULL);

      pthread_t tid;
      for(int i=0;i<threadSize;++i){
        pthread_create(&tid,NULL,threadStart,this);
        tidVec_.push_back(tid);
      }
    }
    ~ThreadPool(){
      pthread_mutex_destroy(&mutex_);
      pthread_cond_destroy(&cond_);

      for(int i=0;i<threadSize_;++i){
        pthread_cancel(tidVec_[i]);
        pthread_join(tidVec_[i],NULL);
      }
    }
    void push(Start* data){
      pthread_mutex_lock(&mutex_);
      que_.push(data);
      pthread_mutex_unlock(&mutex_);
      pthread_cond_signal(&cond_);
    }
    void pop(Start** data){
      pthread_mutex_lock(&mutex_);
      while(0==que_.size())
        pthread_cond_wait(&cond_,&mutex_);
      *data=que_.front();
      que_.pop();
      pthread_mutex_unlock(&mutex_);
    }
  private:
    static void *threadStart(void *arg){
      ThreadPool *ptr=(ThreadPool*)arg;
      while(1){
        Start *p=nullptr;
        ptr->pop(&p);
        p->Run();
        delete[] p;
      }
    }
    int threadSize_;
    std::queue<Start*> que_;
    std::vector<pthread_t> tidVec_;
    pthread_mutex_t mutex_;
    pthread_cond_t cond_;
};
