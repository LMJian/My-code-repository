#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>

int main() {      
    int count = 1;
    int child;
    int i;
    if(!(child = fork())){
        for(i = 0; i <20; i++){
            printf("This is son, his count is: %d. and his pid is: %d\n", i, getpid());
            usleep(500);
        }
    } 
    else{
      for(i=0;i<20;i++){
          printf("This is father, his count is: %d, his pid is: %d\n", count, getpid());
          usleep(300);
      }
        wait(NULL);
    }
    return 0;
}
