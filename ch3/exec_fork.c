#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int doccomand(char* command)
{
  int pid;
  switch(pid=fork())
  {
    case -1:
      return -1;
    case 0:
      execl("/bin/sh","sh","-c",command,NULL);
      exit(127);
  default:
    wait(NULL);
    
  }
  return 0;
      
}

int main()
{
  int pid;
  /* fork child process */
  pid = fork();
  switch(pid){

  case -1:
    perror("fork failed");
    exit(1);

  case 0:
    execl("/bin/ls","ls","-l","--color",NULL);
    perror("execl failed");
    exit(1);

  default:
    wait(NULL);
    printf("Is completed\n");
    exit(0);
  }
}
