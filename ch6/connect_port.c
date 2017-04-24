#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>

#define DEST_IP "166.111.69.52"
#define DEST_PORT 23

main()
{
  int sockfd;
  /* store distant information */

  struct sockaddr_in dest_addr;

  
