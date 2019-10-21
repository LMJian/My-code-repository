#include<unistd.h>
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<fcntl.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<sys/shm.h>
#define IPC_KEY 0x12345678

int main()
{
  int shmid=shmget(IPC_KEY,32,0664);
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
  while(1)
  {
    printf("%s\n",buf);
    sleep(1);
  }
  shmdt(buf);
  shmctl(shmid,IPC_RMID,NULL);
  return 0;
}
