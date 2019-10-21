#include<stdio.h>
#include<stdlib.h>
int main()
{
  int arr[]={1,3,5,6,8,9,4,3,6};
  FILE *file=fopen("test.txt","wb+");
  fwrite(arr,4,9,file);
  fseek(file,0,SEEK_SET);
  int b[10]={0};
  fread(b,4,9,file);
  for(int i=0;i<9;i++)
    printf("%d\n",b[i]);
  fclose(file);

  /*enum{
    SIZE=5
  };
  double a[SIZE]={1.0,2.0,3.0,4.0,5.0};
  double b=0.0;
  size_t ret_code=0;
  FILE *fp=fopen("test.bin","wb");
  fwrite(a,sizeof(*a),SIZE,fp);
  fclose(fp);
  fp=fopen("test.bin","rb");
  while((ret_code=fread(&b,sizeof(double),1,fp))>=1)
  {
    printf("%lf\n",b);
  }
  if(feof(fp))
    printf("Error reading test.bin:unexpected end if file\n");
  else if(ferror(fp))
    perror("Error reading test.bin");
  fclose(fp);
  fp=NULL;
  /*int c;
  FILE* fp=fopen("myfile.txt","r");
  if(!fp)
  {
    perror("File opening failed");
    return EXIT_FAILURE;
  }
  while((c=fgetc(fp))!=EOF)
  {
    putchar(c);
  }
  if(ferror(fp))
    puts("I/O error when reading");
  else if(feof(fp))
    puts("end of file reached successfully");
  fclose(fp);
  /*FILE *pfile;
  long n;
  char buffer[27];

  pfile=fopen("myfile.txt","w+");
  for(n='A';n<='Z';n++)
  {
    fputc(n,pfile);
  }
  rewind(pfile);
  fread(buffer,1,26,pfile);
  fclose(pfile);
  buffer[26]='\0';
  puts(buffer);*/


  /*pfile=fopen("myfile.txt","rb");
  if(pfile==NULL)
  {
    perror("Error opening file");
  }
  else{
    fseek(pfile,0,SEEK_END);
    size=ftell(pfile);
    fclose(pfile);
    printf("size of myfile.txt:%ld bytes.\n",size);
  }*/
  /*pfile=fopen("myfile.txt","wb");
  fputs("This is an apple.",pfile);
  fseek(pfile,9,SEEK_SET);
  fputs(" sam",pfile);
  fclose(pfile);

  /*if(pfile!=NULL)
  {
    fputc('A',pfile);
    fseek(pfile,0,SEEK_SET);
    char ch;
    ch=fgetc(pfile);
    printf("%c\n",ch);

    /*fseek(pfile,0,SEEK_SET);
    char ch[10]={0};
    if(fgets(ch,6,pfile)==NULL)
      printf("shibai!\n");
    printf("11%s\n",ch);

    fclose(pfile);
  }*/
  return 0;

}
