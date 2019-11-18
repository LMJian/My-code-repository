#include<iostream>
#include<stdio.h>
#include<unistd.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<pthread.h>
using namespace std;

void* Func1(void* p){
  struct sockaddr_in* addr=(struct sockaddr_in*)p;
  while(1){
    char* ptr=inet_ntoa(addr->sin_addr);
    printf("add1:%s\n",ptr);
  }
  return NULL;
}
void* Func2(void* p){
  struct sockaddr_in* addr=(struct sockaddr_in*)p;
  while(1){
    char* ptr=inet_ntoa(addr->sin_addr);
    printf("addr2:%s\n",ptr);
  }
  return NULL;
} 
int main(){
  ///pthread_t tid1=0;
  struct sockaddr_in addr1;
  struct sockaddr_in addr2;
  addr1.sin_addr.s_addr=0;
  addr2.sin_addr.s_addr=0xffffffff;
  char *ptr1=inet_ntoa(addr1.sin_addr);
  char *ptr2=inet_ntoa(addr2.sin_addr);
  cout<<ptr1<<endl<<ptr2<<endl;

  /*pthread_create(&tid1,NULL,Func1,&addr1);
  pthread_t tid2=0;
  pthread_create(&tid2,NULL,Func2,&addr2);
  pthread_join(tid1,NULL);
  pthread_join(tid2,NULL);*/
  return 0;
}

