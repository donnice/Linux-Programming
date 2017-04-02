#include <stdio.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>

/* shared memory key */
#define SHMKEY1_t (key_t)0x10
#define SHMKEY2 (key_t)0x15
/* semaphore key */
#define SEMKEY (key_t)0x20

#define BUFSIZ 512
/* buffer size */
#define SIZ 5*BUFSIZ

struct databuf {
  int d_nread;
  char d_buf[SIZ];
};


