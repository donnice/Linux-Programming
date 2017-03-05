#include <signal.h>
#include <stdlib.h>
#include <stdio.h>

int ntimes = 0;

int main()
{
  int pid,ppid;
  int p_action(),c_action();

  /* set parent process SIGUSR1 */
  signal(SIGUSR1,p_action);

  switch(pid=fork()){
  case -1: /* fork failed */
    perror("synchro");
    exit(1);
  case 0:  /* child process mode */
    /* set child process SIGUSR1 */
    signal(SIGUSR1,c_action);

    /* get parent process */
    ppid = getppid();

    for(;;){
      sleep(1);
      kill(ppid,SIGUSR1);
      pause();
    }

    /* dead loop */
    break;

  default: /* parent process mode */
    for(;;){
      pause();
      sleep(1);
      kill(pid,SIGUSR1);
    }
    /* dead loop*/
  }

  return 0;
}

p_action()
{
  printf("Parent caught signal #%d\n",++ntimes);
}

c_action()
{
  printf("Child caught signal #%d\n",++ntimes);
}
