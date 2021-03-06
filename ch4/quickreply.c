#include <stdio.h>
#include <signal.h>

#define TIMEOUT 5
#define MAXTRIES 5
#define LINESIZE 100
#define BELL '\007'
#define TRUE 1
#define FALSE 0

/* decide time out */
static int time_out;

static char inputline[LINESIZE];
char* quickreply(char* prompt);

int main()
{
  printf("%s\n",quickreply("Input"));

  return 0;
}

char* quickreply(char* prompt)
{
  int(*was)(),catch(),ntries;
  char* answer;

  /* set catching the connect of SIGNALRM and save */
  was = signal(SIGALRM,catch);

  for(ntries=0;ntries<MAXTRIES;ntries++)
    {
      time_out=FALSE;
      printf("\n%s>",prompt);

      /* set alarm*/
      alarm(TIMEOUT);

      /* get input*/
      answer = gets(inputline);

      /* close alarm */
      alarm(0);

      if(!time_out)
	break;
    }

  /* retreive the SIGALRM connect */
  signal(SIGALRM,was);

  return(time_out?((char*)0):answer);
}

catch()
{
  /* set sign for timeout */
  time_out = TRUE;

  /* bell warning */
  putchar(BELL);
}

  
