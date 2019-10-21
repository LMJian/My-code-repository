#include<stdio.h>
#include"add.h"
#include"sub.h"
int main()
{
  int a=10;
  int b=20;
  printf("add(%d,%d)=%d\n",a,b,add(a,b));
  a=100;
  b=20;
  printf("sub(%d,%d)=%d\n",a,b,sub(a,b));
  return 0;
}
