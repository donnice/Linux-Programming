#include <stdio.h>
#include <stdlib.h>

#define FIFO_FILE "sampleFIFO"

int main(int argc, char* argv[])
{
  FILE *fp;

  if(argc!=2){
    printf("USAGE:fifoclient [string]\n");
    exit(1);
  }

  /* turn on fifo */
  if((fp=fopen(FIFO_FILE,"w"))==NULL){
    perror("fopen");
    exit(1);
  }

  /* write into pipe */
  fputs(argv[1],fp);

  /* close fifo */
  fclose(fp);
  return 0;
}
