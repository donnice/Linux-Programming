#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>

#define MAX_SEND_SIZE 80

struct mymsgbuf {
  long mtype;
  char mtext[MAX_SEND_SIZE];
};

void send_message(int qid, struct mymsgbuf* qbuf,long type, char *text);
void read_message(int qid, struct mymsgbuf* qbuf,long type);
void remove_queue(int qid);
void change_queue_mode(int qid,char *mode);
void usage(void);

int main(int argc, char *argv[])
{
  key_t key;
  int msgqueue_id;
  struct mymsgbuf qbuf;

  if(argc == 1)
    usage();

  /* Create unique key via call to ftok() */
  key = ftok(".",'m');

  /* Open the queue - create if necessary */
  if((msgqueue_id=msgget(key,IPC_CREAT|0660))=-1){
    perror("msgget");
    exit(1);
  }

  switch(tolower(argv[1][0]))
    {
    case 's':send_message(msgqueue_id,(struct mymsgbuf *)&qbuf,
			   atol(argv[2]),argv[3]); // str to long
      break;

    case 'r':read_message(msgqueue_id, &qbuf, atol(argv[2]));
      break;

    case 'd':remove_queue(msgqueue_id);
      break;
    default:usage();
    }
  return 0;
}

void send_message(int qid, struct mymsgbuf* qbuf, long type,char *text)
{
  
