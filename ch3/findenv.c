#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

extern char** environ;

int pcmp(char* s1, char* s2)
{
  int i=0;

  while(*s1){
    i++;
    if(*s1++!=*s2++)
      return -1;
  }

  return i;
}

char* findenv(char* name)
{
  int len;
  char **p;

  for(p=environ;*p;p++){
    if((len=pcmp(name,*p))>=0 &&
       *(*(p+1))=='=')
      return *(p+1+1);
  }
  return NULL;
}

int main() {
  char** env = environ;
  findenv(*env);

  return 0;
}
  
