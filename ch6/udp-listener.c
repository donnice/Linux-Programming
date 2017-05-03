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

  /* local info */
  struct sockaddr_in my_addr;

  /* connector */
  struct sockaddr_in their_addr;
  int addr_len,numbytes;
  char buf[MAXBUFLEN];
  
  if((sockfd=socket(AF_INET,SOCK_DGRAM,0))==-1){
    perror("socket");
    exit(1);
  }
  /* host endian */
  my_addr.sin_family=AF_INET;

  /* internet endian */
  my_addr.sin_port=htons(MYPORT);

  /* set own IP:machine IP */
  my_addr.sin_addr.s_addr=INADDR_ANY;

  /* bzero */
  bzero(&(my_addr.sin_zero),8);
  
  /* bind port */
  if(bind(sockfd,(struct sockaddr*)&my_addr,sizeof(struct sockaddr))==-1){
    perror("bind");
    exit(1);
  }

  addr_len=sizeof(struct sockaddr);

  if((numbytes=recvfrom(sockfd,buf,MAXBUFLEN,0,
			(struct sockaddr*)&their_addr,&addr_len))==-1){
    perror("recvfrom");
    exit(1);
  }

  printf("got packet from %s\n",inet_ntoa(their_addr.sin_addr));
  printf("packet is %d bytes long\n",numbytes);
  buf[numbytes]='\0';
  printf("packet contains %s\n",buf);

  close(sockfd);
  
}
