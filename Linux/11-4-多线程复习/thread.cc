#include<iostream>
#include<thread>
#include<unistd.h>
#include<mutex>
#include<pthread.h>
#include<atomic>
#include<memory.h>

using namespace std;
mutex Lock;
atomic_int count(0);

#if 0
void Handler()
{
  for(int i=0;i<50000;++i)
  {
    ++count;
  }
  /*while(1)
  {
    Lock.lock();
    printf("hehe---%d,%s\n",num,id.c_str());
    Lock.unlock();
    sleep(1);
  }*/
}
#endif

void Handler(shared_ptr<int> p)
{
  shared_ptr<int> p3(p);
}
int main()
{
  shared_ptr<int> p(new int[10]);
  shared_ptr<int> p2(p);
  thread t1(Handler,p);
  thread t2(Handler,p2);




  /*thread t(Handler);
  thread t2(Handler);
  t.join();
  t2.join();
  printf("count=%d\n",(int)count);*/
  return 0;
}
