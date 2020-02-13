#include<iostream>
#include<unistd.h>
#include<pthread.h>
#include<queue>
using namespace std;

class BlockQueue{
  public:
    BlockQueue(int size)
      :queSize_(size)
  {
    pthread_mutex_init(&mutex_,NULL);
    pthread_cond_init(&eatCond_,NULL);
    pthread_cond_init(&makeCond_,NULL);
  }
    ~BlockQueue(){
      pthread_mutex_destroy(&mutex_);
      pthread_cond_destroy(&eatCond_);
      pthread_cond_destroy(&makeCond_);
    }
    bool full(){
      return que_.size()==queSize_;
    }
    void push(int& data){
      pthread_mutex_lock(&mutex_);
      while(full()){
        pthread_cond_signal(&eatCond_);
        cout<<"i am full. "<<pthread_self()<<endl;
        pthread_cond_wait(&makeCond_,&mutex_);
      }
      que_.push(data);
      cout<<"push "<<data<<" "<<pthread_self()<<endl;
      pthread_cond_signal(&eatCond_);
      pthread_mutex_unlock(&mutex_);
      usleep(1000);
    }
    void pop(int& data){
      pthread_mutex_lock(&mutex_);
      while(que_.empty()){
        pthread_cond_signal(&makeCond_);
        cout<<"i am empty. "<<pthread_self()<<endl;
        pthread_cond_wait(&eatCond_,&mutex_);
      }
      data=que_.front();
      que_.pop();
      cout<<"pop "<<data<<" "<<pthread_self()<<endl;
      pthread_cond_signal(&makeCond_);
      pthread_mutex_unlock(&mutex_);
      usleep(1000);
    }
  private:
    queue<int> que_;
    size_t queSize_;
    pthread_mutex_t mutex_;
    pthread_cond_t eatCond_;
    pthread_cond_t makeCond_;
};

#define PTHREADCOUNT 10     //生产者和消费者线程数
int count=20;          //总共生产数量
pthread_mutex_t lock;      //互斥锁

void *makeStart(void* arg){   //生产
  BlockQueue* ptr=(BlockQueue*)arg;
  while(1){
    pthread_mutex_lock(&lock);
    if(count<=0){
      pthread_mutex_unlock(&lock);
      break;
    }
    ptr->push(count);
    --count;
    pthread_mutex_unlock(&lock);
  }
  return nullptr;
}
void *eatStart(void* arg){   //消费
  BlockQueue* ptr=(BlockQueue*)arg;
  while(1){
    int data;
    ptr->pop(data);
  }
  return nullptr;
}

int main(){
  BlockQueue que(5);  //设置等待队列大小
  pthread_mutex_init(&lock,NULL);
  pthread_t eat[PTHREADCOUNT],make[PTHREADCOUNT];
  for(int i=0;i<PTHREADCOUNT;++i){
    pthread_create(&eat[i],NULL,eatStart,&que);
    pthread_create(&make[i],NULL,makeStart,&que);
  }


  for(int i=0;i<PTHREADCOUNT;++i){
    pthread_join(eat[i],NULL);
    pthread_join(make[i],NULL);
  }
  pthread_mutex_destroy(&lock);
  return 0;
}
