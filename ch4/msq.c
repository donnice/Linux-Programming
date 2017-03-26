#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <stdio.h>


struct mymsgbuf {
    long mtype;        /* Message type */
    int request;       /* work request number */
    double salary;
};

/* msgget() */
int open_queue(key_t keyval)
{
  int qid;

  if((qid=msgget(keyval,IPC_CREAT|0660))==-1)
    {
      return -1;
    }

  return qid;
}

int send_message(int qid,struct mymsgbuf* qbuf)
{
  int result,length;

  /* The length is the size of structure minus sizeof(mtype)*/
  length = sizeof(struct mymsgbuf)-sizeof(long);
  if((result=msgsnd(qid,qbuf,length,0))==-1)
    {
      return -1;
    }
  return result;
}

int read_message(int qid,long type,struct mymsgbuf* qbuf)
{
  int result,length;

  length=sizeof(struct mymsgbuf)-sizeof(long);

  if((result=msgrcv(qid,qbuf,length,type,0))==-1)
    {
      return -1;
    }

  return result;
}

/* check whether eligible message in queue */
/*int peek_message(int qid, long type)
 *{
 * int result,length;
 * if((result=msgrcv(qid,NULL,0,type,IPC_NOWAIT))==-1)
 *  {
 *    if(errno==E2BIG)
 *	return TRUE;
 *  }
 *
 *return FALSE;
} */

/* IPC_STAT */
int get_queue_ds(int qid,struct msgqid_ds *qbuf)
{
  if(msgctl(qid,IPC_STAT,qbuf)==-1)
    {
      return -1;
    }

  return 0;
}

/* IPC_SET */
int change_queue_mode(int qid,char *mode)
{
  struct msqid_ds tmpbuf;

  /* retrieve a current copy of the internal ds */
  get_queue_ds(qid,&tmpbuf);
  
  /* change permission */
  sscanf(mode,"%ho",&tmpbuf.msg_perm.mode);

  /* Update the internal ds */
  if(msgctl(qid,IPC_SET,&tmpbuf)==-1)
    {
      return -1;
    }

  return 0;
}

int remove_queue(int qid)
{
  if(msgctl(qid,IPC_RMID,0)==-1)
    {
      return -1;
    }

  return 0;
}

  
int main()
{
  int qid;
  key_t msgkey;
  struct mymsgbuf msg;

  /* Generate our IPC key value */
  msgkey=ftok(".",'m');    /* convert pathname to Sys V */

  /* Open/create the queue */
  if((qid=open_queue(msgkey))==-1) {
    perror("open_queue");
    exit(1);
  }

  /* load up the message */
  msg.mtype=1;    /* must be a positive num */
  msg.request=1;  /* Data element 1 */
  msg.salary=1000.00;

  if((send_message(qid,&msg))==-1){
    perror("send_message");
    exit(1);
  }
}
    
