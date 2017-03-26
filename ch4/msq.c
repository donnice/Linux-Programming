#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>

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
    
