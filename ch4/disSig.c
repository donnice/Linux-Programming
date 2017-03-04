#include <stdlib.h>
#include <stdio.h>
#include <signal.h>

int main(void)
{
  signal(SIGINT,SIG_IGN); /* tell the process ignore signal */
  printf("xixi\n");
  sleep(10); /* second */
  printf("end\n");
  return;
}
