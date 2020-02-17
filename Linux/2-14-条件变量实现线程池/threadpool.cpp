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
     ,threadCurNum_(0)
    {
      pthread_mutex_init(&mutex_,NULL);
      pthread_cond_init(&cond_,NULL);
      
      isQuit_=false;
      pthread_t tid;
      for(int i=0;i<threadSize;++i){
        pthread_create(&tid,NULL,threadStart,this);
        ++threadCurNum_;
      }
    }
    ~ThreadPool(){
      pthread_mutex_destroy(&mutex_);
      pthread_cond_destroy(&cond_);
    }
    void push(Start* data){
      pthread_mutex_lock(&mutex_);
      if(isQuit_){
        pthread_mutex_unlock(&mutex_);  //释放线程就不允许再增加数据了
      }
      que_.push(data);
      pthread_mutex_unlock(&mutex_);
      pthread_cond_signal(&cond_);
    }
    void pop(Start** data){
      pthread_mutex_lock(&mutex_);
      while(0==que_.size()){
        if(isQuit_){         //释放线程池
          --threadCurNum_;  
          pthread_mutex_unlock(&mutex_);
          pthread_exit(NULL);   //线程退出
        }
        pthread_cond_wait(&cond_,&mutex_);
      }
      *data=que_.front();
      que_.pop();
      pthread_mutex_unlock(&mutex_);
    }
    void threadClear(){
      pthread_mutex_lock(&mutex_);
      isQuit_=true;                   //标记要释放线程池里的线程
      pthread_mutex_unlock(&mutex_);
      if(threadCurNum_>0)
        pthread_cond_broadcast(&cond_);  //唤醒所有线程去争抢锁资源
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
    bool isQuit_;
    int threadCurNum_;
    pthread_mutex_t mutex_;
    pthread_cond_t cond_;
};
