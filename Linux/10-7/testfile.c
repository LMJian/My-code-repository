#include <stdio.h>
#include <string.h>
int main()
{
    const char *msg0="hello printf";
      const char *msg1="hello fwrite";
        const char *msg2="hello write";
          printf("%s", msg0);
            fwrite(msg1, strlen(msg0), 1, stdout);
              write(1, msg2, strlen(msg2));
                fork();
                  return 0;                  
}
