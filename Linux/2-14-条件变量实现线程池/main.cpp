#include "threadpool.cpp"
using namespace std;

#define ThreadSize 10
#define MyStartCount 100

class MyStart:public Start{
  public:
    MyStart(int id)
      :Start(id)
    {}
    void Run()override{
      cout<<"id= "<<id_<<",thread="<<pthread_self()<<endl;
      usleep(300);
    }
};
int main(){
  ThreadPool pool(ThreadSize);
  for(int i=0;i<MyStartCount;++i){
    MyStart *p=new MyStart(i);
    pool.push(p);
  }
  //while(1)
    sleep(6);
  pool.threadClear();
  return 0;
}
