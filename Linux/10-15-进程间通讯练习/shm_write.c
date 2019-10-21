#include<unistd.h>
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<fcntl.h>
#include<sys/types.h>
#include<sys/stat.h>
#define IPC_KEY 0x12345678 
#include<sys/shm.h>
int main()
{
  int shmid=shmget(IPC_KEY,32,IPC_CREAT|0664);
  if(shmid==-1)
  {
    perror("shmget errno");
    exit(-1);
  }
  char *buf=shmat(shmid,NULL,0);
  if(buf==(void*)-1)
  {
    perror("shmat errno");
    exit(-1);
  }
  int i=0;
  sleep(5);
  while(i<26)
  {
    buf[i]='A'+i;
    i++;
    buf[i]=0;
    sleep(1);
  }
  shmdt(buf);

  return 0;
}
