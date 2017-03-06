#include <stdio.h>
#include <signal.h>

#define TRUE 1
#define FALSE 0
#define BELLS "\007\007\007"

int alarm_flag=FALSE;

/* SIGALARM processing */
setflag()
{
  alarm_flag=TRUE;
}

int main(int argc, char* argv[])
{
  int nsecs;
  int i;

  if(argc<2)
    {
      fprintf(stderr,"Usage:tml #minutes message\n");
      exit(1);
    }

  if((nsecs=atoi(argv[1])*60)<=0)
    {
      fprintf(stderr,"Invalid time\n");
      exit(2);
    }

    /* set SIGALARM related action */
    signal(SIGALRM,setflag);

    /* set alarm */
    alarm(nsecs);

    /* use pause() to wait for signal */
    pause();

    if(alarm_flag)
      {
	printf(BELLS);
	for(i=2;i<argc;i++){
	  printf("%s\n",argv[i]);
	}
      }
    exit(0);

    return 0;
    }
