#include"comm.h"

int main()
{
  int shmid=getShm(4096);
  sleep(1);
  char *addr=shmat(shmid,NULL,0);
  sleep(2);
  int i=0;
  while(i<26)
  {
    addr[i]='A'+i;
    i++;
    addr[i]=0;
    sleep(1);
  }
  shmdt(addr);
  sleep(2);
  return 0;
}
