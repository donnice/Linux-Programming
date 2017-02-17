#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main()
{
  char* av[] = {"ls","-l",NULL};
  execv("/bin/ls",av);
  perror("execv failed");
  exit(1);
}
