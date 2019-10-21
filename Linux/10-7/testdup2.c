#include<stdio.h>
#include<unistd.h>
#include<fcntl.h>
int main()
{
int fd = open("myfile", O_WRONLY|O_CREAT, 00644);
 if(fd < 0){
    perror("open");
     return 1;
      
 }
 dup2(fd,1);
  printf("fd: %d\n", fd);
   fflush(stdout);

    close(fd);
    return 0;
}
