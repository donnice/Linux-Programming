int open_semaphore_set(key_t keyval, int numsems)
{
  int sid;

  if(!numsems)
    return -1;
  if((sid=semget(keyval,numsems, IPC_CREAT|0660))==-1)
    {
      return -1;
    }
  return sid;
}

/* semop() change status of signal */
/*set first(0) signal -1 */
struct sembuf sem_get={0,-1,IPC_NOWAIT};
if((semop(sid,&sem_get,1))==-1)
  perror("semop");    // run it use semop
/* release */
struct sembuf sem_release={0,1,IPC_NOWAIT};
semop(sid,&sem_release,1);

int get_sem_val(int sid, int semnum)
{
  return (semctl(sid,semnum,GETVAL,0));
}

void init_semaphore(int sid, int semnum, int initval)
{
  union semun semopts;

  semopts.val=initval;
  semctl(sid, semnum, SETVAL,semopts);
}
