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
   
