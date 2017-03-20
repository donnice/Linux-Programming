#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
  FILE *pipe_fp, *infile;
  char readbuf[80];

  if(argc!=3){
    fprintf(stderr,"USAGE:popen3 [command][filename]\n");
    exit(1);
  }

  /* open file*/
  if((infile=fopen(argv[2],"rt"))==NULL)
    {
      perror("fopen");
      exit(1);
    }

  /* build write pipe */
  if((pipe_fp=popen(argv[1],"w"))==NULL)
    {
      perror("popen");
      exit(1);
    }

  /* processing loop */
  do {
    fgets(readbuf,80,infile);
    if(feof(infile))break; /* end of file */
    fputs(readbuf,pipe_fp);
  } while(!feof(infile));

  fclose(infile);
  pclose(pipe_fp);

  return 0;
}
    
  
