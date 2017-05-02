#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <netdb.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>

#define PORT 4000

#define MAXDATASIZE 100

int main(int argc,char* argv[])
{
  int sockfd,numbytes;
  char buf[MAXDATASIZE];

  struct hostent *he;
  /* connector */
  struct sockaddr_in their_addr;

  /* check argc */
  if(argc != 2) {
    fprintf(stderr,"usage:client hostname\n");
    exit(1);
  }

  /* host */
  if((he=gethostbyname(argv[1]))==NULL) {
    herror("gethostbyname");
    exit(1);
  }

  if((sockfd = socket(AF_INET,SOCK_STREAM,0))==-1) {
    perror("socket");
    exit(1);
  }

  /* host endianess */
  their_addr.sin_family=AF_INET;

  /* internet endianess */
  their_addr.sin_port = htons(PORT);
  
  their_addr.sin_addr=*((struct in_addr*)he->h_addr);
  /* bzero the rest */
  bzero(&(their_addr.sin_zero),8);

  if(connect(sockfd,(struct sockaddr *)&their_addr,sizeof(struct sockaddr))==-1){
    perror("connect");
    exit(1);
  }

  if((numbytes=recv(sockfd,buf,MAXDATASIZE,0))==-1){
    perror("recv");
    exit(1);
  }

  buf[numbytes]='\0';
  printf("Received:%s",buf);
  close(sockfd);
  return 0;
}
      
