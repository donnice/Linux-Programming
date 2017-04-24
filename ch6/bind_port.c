#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>

#define MYPORT 4000

main()
{
  int sockfd;

  struct sockaddr_in my_addr;

  sockfd = socket(AF_INET,SOCK_STREAM,0);
  my_addr.sin_family=AF_INET;       /* host byte sequance */
  my_addr.sin_port=htons(MYPORT);   /* internet byte sequence */
  my_addr.sin_addr.s_addr=inet_addr("166.111.69.52");
  bzero(&(my_addr.sin_zero),8);     /* erases the data in n bytes of mem */

  if(bind(sockfd,(struct sockaddr*)&my_addr,sizeof(struct sockaddr))==-1){
    perror("bind error!");
    exit(1);
  }
}
