#include "smallsh.h"

static char inpbuf[MAXBUF],tokbuf[2*MAXBUF],
  *ptr=inpbuf,*tok=tokbuf;

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
