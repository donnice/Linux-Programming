#include <strings.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

static int num=0;
static char namebuf[20];
static char prefix[]="/tmp/tmp";

char* gentemp()
{
  int length,pid;
  /* get process id */
  pid = getpid();

  strcpy(namebuf,prefix);
  length=strlen(namebuf);
  /* add pid */
  itoa(pid,&namebuf[length]);

  strcat(namebuf,".");
  length=strlen(namebuf);

  do{
    /* add subfix number */
    itoa(num++,&namebuf[length]);
  }while(access(namebuf,0)!=-1);
  return namebuf;
}

/* itoa transfer int to char */
itoa(int i, char* string)
{
  int power,j;

  j=i;
  for(power=1;j>=10;j/=10)
    power*=10;
  for(;power>0;power/=10){
    *string++='0'+i/power;
    i%=power;
  }
  *string='\0';
}

int main() {
  int newpgid;

  newpgid=setpgrp();
  printf("%d",newpgid);

  return 0;
}
