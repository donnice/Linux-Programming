#include "share_ex.h"

#define IFLAGS (IPC_CREAT|IPC_EXCL)
#define ERR ((struct databuf*)-1)

static int shmid1, shmid2, semid;

struct sembuf p1={0,-1,0},
  p2={1,-1,0},
  v1={0,1,0},
  v2={1,1,0};

reader(int semid,struct databuf *buf1, struct *buf2);

fatal(char *mes)
{
  perror(mes);
  exit(1);
}

getseg(struct databuf** p1, struct databuf** p2)
{
  /* build shared memory */
  if((shmid=shmget(SHMKEY1,sizeof(struct databuf),0600|IFLAGS))<0)
    fatal("shmget");

  /* Build connect between shared memory */
  if((*p1=(struct databuf*)(shmat(shmid1,0,0)))==ERR)
    fatal("shmat");

  if((*p2=(struct databuf*)(shmat(shmid1,0,0)))==ERR)
    fatal("shmat");

}

int getsem()
{
  /* Build signal object */
  if((semid=semget(SEMKEY,2,0600|IFLAGS))<0)
    fatal("semget");

  /* Initialize signal */
  if(semctl(semid,0,SETVAL,0)<0)
    fatal("semctl");

  if(semctl(semid,1,SETVAL,0)<0)
    fatal("semctl");

  return semid;
}

remove()
{
  if(shmctl(shmid1,IPC_RMID,NULL)<0)
    fatal("shmctl");

  if(shmctl(shmid2,IPC_RMID,NULL)<0)
    fatal("shmctl");
  if(shmctl(semid,IPC_RMID,NULL)<0)
    fatal("semctl");
}

main()
{
  int semid,pid;
  struct datebuf *buf1, *buf2;

  /* initialize signal */
  semid=getsem();

  /* Build and connect shared memory */
  getseg(&buf1,&buf2);

  switch(pid=fork()){
  case -1:
    fatal("fork");

  case 0:
    writer(semid,buf1,buf2);
    remove();
    break;

  default:
    reader(semid,buf1,buf2);
    break;
  }

  exit(0);
}

reader(int semid, struct databuf *buf1, struct databuf *buf2)
{
  for(;;){

    /* read into buf1 */
    buf1->dnread=read(0,buf1->d_buf,SIZ);

    /* synchronize */
    semop(semid,&v1,1);
    semop(semid,&p2,1);

    /* prevent writer from sleep */
    if(buf1->d_nread<=0)
      return;

    buf2->d_nread(0,buf2->d_buf,SIZ);

    semop(semid,&v2,1);
    semop(semid,&p1,1);

    if(buf2->d_nread<=0)
      return;
  }
}
