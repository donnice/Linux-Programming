int open_shm(key_t keyval, int segsize)  /* build new or get exist shm */
{
  int shmid;

  if((shmid=shmget(keyval,segsize,IPC_CREAT|0660))==-1)
    {
      return -1;
    }

  return shmid;
}

/* shared memory to self process space */
char *attach_segment(int shmid) /* shmaddr=0,shmflg  */
{
  return (shmat(shmid,0,0));
}

/* shmctl() */
/* shmdt() stop map if not shm no longer necessary */



