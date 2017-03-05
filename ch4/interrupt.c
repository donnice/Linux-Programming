#include <signal.h>
#include <stdio.h>
#include <stdlib.h>

int interrupt()
{
  printf("Interrupt called\n");
  sleep(3);
  printf("Interrupt Func Ended.\n");
}

int catchquit()
{
  printf("Quit called\n");
  sleep(3);
  printf("Quit ended.\n");
}

int main()
{
  signal(SIGINT,interrupt);
  signal(SIGQUIT,catchquit);
  printf("Interrupt set for SIGINT\n");
  sleep(10);
  printf("Program NORMAL ended.\n");
  return 0;
}
