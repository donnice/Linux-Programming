#include <stdlib.h>
#include <stdio.h>
#include <signal.h>

int catch(int sig);

int main(void)
{
  signal(SIGINT,catch);/* connect SIGINT signal and catch */
  printf("xixi\n");
  sleep(10);
  printf("end\n");
  return 0;
}

int catch(int sig)
{
  printf("Catch succeed!\n");
  return 1;
}
