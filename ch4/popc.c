#include <stdio.h>

#define MAXSTRS 5

/* create a pipe, and performs fork/exec operations use "command" */

int main(void)
{
  int cntr;
  FILE *pipe_fp;
  
  char *strings[MAXSTRS] = {"roy","zixia","gouki","supper","mmwan"};

  if((pipe_fp=popen("sort","w"))==NULL){
    perror("popen");
    exit(1);
  }

  /* process loop*/
  for(cntr=0;cntr<MAXSTRS;cntr++){
    fputs(strings[cntr],pipe_fp);
    fputc('\n',pipe_fp);
  }

  /* close pipe */
  pclose(pipe_fp);
  return 0;
}
