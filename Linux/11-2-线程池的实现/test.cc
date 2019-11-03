#include"threadpool.hpp"
#include<sys/syscall.h>
#include<unistd.h>
#include<stdio.h>


class MyStack:public Stack{
  public:
    MyStack(int n)
      :_id(n)
    {}
    virtual void Run()override
    {
      printf("MyStack---tid=%d,id=%d\n",syscall(SYS_gettid),_id);
    }
    virtual ~MyStack()override
    {}
  private:
    int _id;
};

int main()
{
  ThreadPool pool(10);
  for(int i=0;i<20;++i)
  {
    pool.AddStack(new MyStack(i));
  }
  while(1)
    sleep(1);

  return 0;
}
