#include <stdio.h>
#include <strings.h>
#include <unistd.h>
#include <stdlib.h>

extern char** environ; /* initiated somewher */

int main()
{
  char** env = environ;

  while(*env) {
    printf("%s\n",*env++);
  }

  return 0;
}
