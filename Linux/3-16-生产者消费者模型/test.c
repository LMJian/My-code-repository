#include<iostream>
#include<unistd.h>
#include<pthread.h>
#include<queue>
using namespace std;

template<class T>
class pool{
  public:
    pool(){
      pthread_cond_init(&_cond,NULL);
      pthread_mutex_init(&_mutex,NULL);
    }
    ~pool(){
      pthread_cond_destroy(&_cond);
      pthread_mutex_destroy(&_mutex);
    }
    void push(const T& data){
      pthread_mutex_lock(&_mutex);
      _arr.push(data);
      pthread_mutex_unlock(&_mutex);
      pthread_cond_signal(&_cond);
    }
    void pop(T& data){
      pthread_mutex_lock(&_mutex);
      while(0==_arr.size())
        pthread_cond_wait(&_cond,&_mutex);
      data=_arr.front();
      _arr.pop();
      pthread_mutex_unlock(&_mutex);
    }
  private:
    queue<T> _arr;
    pthread_cond_t _cond;
    pthread_mutex_t _mutex;
};
