#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main()
{
  printf("Executing ls\n");
  execl("/bin/ls","ls","-l",NULL); // path, arg, ...

  perror("excel failed to run ls");
  exit(1);
}
