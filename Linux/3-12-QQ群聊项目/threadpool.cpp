#include<iostream>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<queue>

class Start{
  public:
    virtual void Run(){
      printf("Start is running!!!\n");
    }
};

class ThreadPool{
  public:
    ThreadPool(int Size)
    :threadCurNum_(Size)
    {
      pthread_mutex_init(&mutex_,NULL);
      pthread_cond_init(&cond_,NULL);

      isQuit_=false;
      pthread_t tid;
      for(int i=0;i<Size;++i){
        pthread_create(&tid,NULL,threadStart,this);
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
        return;
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
          std::cout<<"exit"<<std::endl;
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
    void threadCapacity(){

    }
    static void *threadStart(void *arg){
      ThreadPool *ptr=(ThreadPool*)arg;
      while(1){
        Start *p=nullptr;
        ptr->pop(&p);
        p->Run();
        delete[] p;
      }
    }
    std::queue<Start*> que_;
    bool isQuit_;
    int threadCurNum_;     //现存线程个数
    pthread_mutex_t mutex_;
    pthread_cond_t cond_;
};
