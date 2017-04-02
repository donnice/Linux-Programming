#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>

#define SEGSIZE 100

int main(int argc, char* argv[])
{
  key_t key;
  int shmid,cntr;
  char *segptr;

  if(argc==1)
    usage();

  /* Create Unique key via call to ftok() */
  key=ftok(".",'S');

  /* Open the sm segment-create if not exist */
  if((shmid=shmget(key,SEGSIZE,IPC_CREAT|IPC_EXCL|0666))==-1)
    {
      printf("Shared memory segment exists - opening as client\n");

      if((shmid=shmget(key,SEGSIZE,0))==-1)
	{
	  perror("sh,get");
	  exit(1);
	}
    }

  else
    {
      printf("Creating new shared memory segment\n");
    }

  /* Attach (map) the sm into current process */
  if((segptr=shmat(shmid,0,0))==-1)
    {
      perror("shmat");
      exit(1);
    }

  switch(tolower(argv[1][0]))
    {
    case 'w':writeshm(shmid,segptr,argv[2]);
      break;

    case 'r':readshm(shmid,segptr);
      break;

    case 'd':removeshm(shmid);
      break;

    case 'm':changemode(shmid, argv[2]);
      break;

    default:usage();
    }
}
