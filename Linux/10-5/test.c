#include<stdio.h>

int main()
{
  const char *msg="hello fwrite\n";
  fwrite(msg,strlen(msg),1,stdout);

  printf("hello printf\n");
  fprintf(stdout,"hello fprintf\n");
  return 0;
  /*char *file="./tmp.txt";
  FILE *fp=fopen(file,"w+");
  if(fp==NULL)
  {
    perror("fopen error");
    return -1;
  }
  char buf[1024]="下课吃饭~~\n";
  fwrite(buf,1,strlen(buf),fp);
  fseek(fp,0,SEEK_SET);
  memset(buf,0x00,1024);
  int ret=fread(buf,1,1023,fp);
  //perror("fread error");
  if(feof(fp))
  {
    printf("end of file!!\n");
  }
  printf("buf:[%d-%s]\n",ret,buf);
  fclose(fp);*/
  return 0;
}
