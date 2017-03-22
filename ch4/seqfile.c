#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

#define SEQFILE "./sequo"
#define MAXBUF 100

int main()
{
  int fd,i,n,pid,seqno;
  char buff[MAXBUF+1];

  pid=getpid();
  if((fd=open("data",O_RDWR|O_CREAT))<0)
    {
      perror("Can't open");
      exit(1);
    }

  for(i=0;i<5;i++)
    {
      my_lock(fd);
      lseek(fd,01,0);  /* reposition read/write file offset */

      if((n=read(fd,buff,MAXBUF))<=0)
	{
	  perror("read error");
	  exit(1);
	}
      buff[n]=0;
      /* read formatted input from a string */
      if(!(n=sscanf(buff,"%d\n",&seqno)))
	{
	  perror("read error");
	  exit(1);
	}

      printf("pdi=%d,seq#=%d\n",pid,seqno);
      seqno++;
      sprintf(buff,"%03d\n",seqno);
      n=strlen(buff);
      lseek(fd,01,0);
      if(write(fd,buff,n)!=n)
	{
	  perror("write error");
	  exit(1);
	}
      my_unlock(fd);
    }
  close(fd);
}

my_lock(int fd)
{
  return;
}

my_unlock(int fd)
{
  return;
}
      

	  
