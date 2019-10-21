#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<errno.h>
#include<signal.h>

void sigcb(int sig)
{
  printf("recv a signal: %d\n",sig);
  //sigaction(signo,&old,NULL);(如果定义的是全局变量，可以这样恢复)
}
int main()
{
  sigset_t set,oldset;
  sigemptyset(&set);
  //sigfillset(&set);
  sigaddset(&set,SIGINT);
  sigaddset(&set,SIGQUIT);
  sigprocmask(SIG_BLOCK,&set,&oldset);
  struct sigaction act,old;
  act.sa_handler=sigcb;
  act.sa_flags=0;
  sigemptyset(&act.sa_mask);
  sigaction(SIGINT,&act,&old);//signal(SIGINT,sigcb);
  sigaction(SIGQUIT,&act,&old);//signal(SIGQUIT,sigcb);

  printf("press enter to continue");
  getchar();

  act.sa_handler=SIG_IGN;//SIG_DFL默认,SIG_IGN忽略
  //方法1
  //sigaction(SIGINT,&act,NULL);//signal(SIGINT,SIG_DFL);
  //sigaction(SIGQUIT,&act,NULL);//signal(SIGQUIT,SIG_DFL);
  //方法2
  //sigaction(SIGINT,&old,NULL);
  //sigaction(SIGQUIT,&old,NULL);

  sigprocmask(SIG_UNBLOCK,&set,NULL);
  while(1);
  return 0;

}
