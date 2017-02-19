#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

failure(char *s)
{
  perror(s);
  exit(1);
}

printpos(char* strings, int filds)
{
  long pos;
  if((pos=lseek(filds,0L,1))<0L)
    failure("lseek failed"); // move the read/write file offset
  printf("%s:%ld\n",strings,pos);
}

int main()
{
  int fd;  // file description
  int pid; // process description
  char buf[10]; /* data buffer */
  /* open file */
  if((fd=open("data",O_RDONLY))<0)
    failure("open failed");
  read(fd,buf,10); /* advance file pointer */
  printpos("Before fork",fd);
  /* fork new process */
  if((pid=fork())<0)
    failure("fork failed");
  else if(!pid)
  {
    /* child process */
    printpos("Child before read",fd);
    read(fd,buf,10);
    printpos("Child after read",fd);
  } else {
    /* parent process */
    /* wait until the end of child process */
    wait(NULL);
    printpos("parent after wait",fd);
  }
}
  
