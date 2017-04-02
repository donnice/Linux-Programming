#include <stdio.h>
#include <stdlib.h>
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

void writeshm(int shmid, char *segptr, char *text)
{
  strcpy(segptr,text);
  printf("Done...\n");
}

void readshm(int shmid,char *segptr)
{
  printf("segptr:%s\n",segptr);
}

void removeshm(int shmid)
{
  shmctl(shmid,IPC_RMID,0);
  printf("Shared mem segment marked for deletion\n");
}

void changemode(int shmid, char *mode)
{
  struct shmid_ds myshmds;

  /* Get current values for internal ds */
  shmctl(shmid,IPC_STAT,&myshmds);

  /* Display old permissions */
  printf("Old permissions were: %o\n",myshmds.shm_perm.mode);

  /* Convert and load the mode */
  sscanf(mode,"%o",&myshmds.shm_perm.mode);

  /*update mode */
  shmctl(shmid,IPC_SET,&myshmds);

  printf("New permissions are:%o\n",myshmds.shm_perm.mode);
}

void usage()
{
  fprintf(stderr,"shmtool - A utility for tinkering with sm\n");
  fprintf(stderr,"\nUSAGE: shmtool (w)rite <text>\n");
  fprintf(stderr,"                 (r)ead\n");
  fprintf(stderr,"                 (d)elete\n");
  fprintf(stderr,"                 (m)ode change <octal mode>\n");
  exit(1);
}
