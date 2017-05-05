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

int main(int argc, char *argv[])
{
	int sockfd, numbytes,new_fd;
	char buf[MAXDATASIZE];

	struct hostent *he;
	
	struct sockaddr_in their_addr;

	if(argc!=2)
	{
		fprintf(stderr,"usage:client hostname\n");
		exit(1);
	}

	if((he=gethostbyname(argv[1]))==NULL)
	{
		herror("gethostbyname");
		exit(1);
	}

	if((sockfd=socket(AF_INET,SOCK_STREAM,0))==-1)
	{
		perror("socket");
		exit(1);
	}

	their_addr.sin_port=htons(PORT);
	their_addr.sin_family=AF_INET;
	their_addr.sin_addr=*((struct in_addr*)he->h_addr);

	bzero(&(their_addr.sin_zero),8);

	if(connect(sockfd,(struct sockaddr*)&their_addr,sizeof(struct sockaddr))==-1)
	{
		perror("connect");
		exit(1);
	}

	if(send(new_fd,"123",3,0)==-1)
	{
		perror("send");
		close(new_fd);
		exit(0);
	}
	printf("Send 3 bytes of normal data\n");
	sleep(1);

	if(send(new_fd,"4",1,MSG_OOB)==-1)
	{
		perror("send");
		close(new_fd);
		exit(0);
	}
	printf("Send 1 byte of OOB data\n");
	sleep(1);
	close(sockfd);
	return 0;
}
	
