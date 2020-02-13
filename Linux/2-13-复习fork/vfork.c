#include<stdio.h>
#include<unistd.h>
#include<sys/wait.h>
#include<sys/types.h>
#include<stdlib.h>

int main() {
  int count = 1;
  int child;
  printf("Before create son, the father's count is:%d\n", count);
  if(!(child = fork())){
      int i;
      for(i=0;i<100;++i){
        printf("This is son,The i is:%d\n",i);
        count++;
        if(i==20){
          printf("This is son,his pid is:%d and the count is:%d\n",getpid(),++count);
          exit(1);
        }
      }
      usleep(600);
  }
  else {
    printf("After son, This is father, his pid is: %d and the count is: %d, and the child is: %d\n", getpid(), count, child);
    wait(NULL);
  }
  return 0;
}
