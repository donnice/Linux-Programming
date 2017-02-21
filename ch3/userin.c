#include "smallsh.h"

static char inpbuf[MAXBUF],tokbuf[2*MAXBUF],
  *ptr=inpbuf,*tok=tokbuf;

static char special[]={' ','\t','*',';','\n','\0'};

int inarg(char c)
{
  char *wrk;
  for(wrk=special;*wrk!='\0';wrk++)
    if(c==*wrk)
      return(0);
  return(1);
}

/* userin() */
int userin(char* p)
{
  int c, count;
  ptr = inpbuf;
  tok = tokbuf;
  /* display notification */
  printf("%s",p);
  
  while(true) {
    if((c=getchar())==EOF)
      return(EOF);
    if(count<MAXBUF)
      inpbuf[count++]=c;
    if(c=='\n' && count<MAXBUF) {
      inpbuf[count]='\0';
      return(count);
    }

    /* if too long, reinput */
    if(c=='\n'){
      printf("smallsh:input line too long\n");
      count = 0;
      printf("%s",p);
    }
  }
}

int gettok(char* output)
{
  int type;

  outptr = tok;
  for(;*ptr==''||*ptr=='\t';ptr++);
  *tok++=*ptr;
  switch(*ptr++){
  case '\n':
    type=EOL;
    break;
  case '&':
    type=AMPERSAND;
    break;
  case ';':
    type=SEMICOLON;
    break;
  default:
    type=ARG;
    while(inarg(*ptr))
      *tok++=*ptr++;
  }
  *tok++='\0';
  return type;
}

procline()
{
  char* arg[MAXARG+1];
  int toktype;
  int narg;
  int type;

  for(narg=0;;) {
    switch(toktype=gettok(&arg[narg])) {

    case ARG:
      if(narg<MAXARG)
	narg++;
      break;
    case EOL:
    case SEMICOLON:
    case AMPERSAND:
      type=(toktype==AMPERSAND)?BACKGROUND:FOREGROUND;
      if(narg!=0){
	arg[narg]=NULL;
	runcommand(arg,type);
      }
      if(toktype==EOL)
	return;
      narg=0;
      break;
    }
  }
}

runcommand(char** cline, int where)
{
  int pid,exitstat,ret;

  if((pid=fork())<0){
    perror("fork fail");
    return(-1);
  }
  if(!pid){/* child process */
    execvp(*cline,cline);
    perror(*cline);
    exit(127);
  }
  /* parent */
  /* background */
  if(where==BACKGROUND){
    printf("[process id %d]\n",pid);
    return(0);
  }

  /* front desk */
  while((ret=wait(&exitstat))!=pid&&ret!=-1);
  return(ret==-1?-1:exitstat);
}

char *prompt="command>";

int main()
{
  while(userin(prompt)!=EOF)
    procline();
}
   
