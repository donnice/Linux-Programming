#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/wait.h>

#define MYPORT 5000

#define MAXBUFLEN 100

main()
{
  int sockfd;

  /* self info */
  struct sockaddr_in my_addr;
