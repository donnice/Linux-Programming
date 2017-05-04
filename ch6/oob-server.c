#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <unistd.h>

/* local port */
#define MYPORT 4000

#define BACKLOG 10

void sig_urg(int signo);

main()
{
	/* listen at sock_fd, accept new conn at new_fd */
	int sock_fd,new_fd;
	/* for SIGURL */
	void *old_sig_urg_handle;
	/* local addr */
	struct sockaddr_in my_addr;

	/* connector addr */
	struct sockaddr_in their_addr;
	
	int sin_size;
	int n;
	char buff[100];

	if((sock_fd = socket(AF_INET,SOCK_STREAM,0))==-1)
	{
		perror("socket");
		exit(1);
	}

	/* host endiness */
	my_addr.sin_family = AF_INET;
	
	/* internet endiness */
	my_addr.sin_port = htons(MYPORT);
	
	/* host IP tp s_addr */
	my_addr.sin_addr.s_addr=INADDR_ANY;

	bzero(&(my_addr.sin_zero),8);

	if(bind(sock_fd,(struct sockaddr*)&my_addr,
	sizeof(struct sockaddr))==-1)
	{
		perror("bind");
		exit(1);
	}
	
	old_sig_urg_handle=signal(SIGURG,sig_urg);
	/* change connfd owner */
	fcntl(sock_fd,F_SETOWN,getpid());

	while(1)
	{
		sin_size = sizeof(struct sockaddr_in);

		if((new_fd=accept(sock_fd,(struct sockaddr*)&their_addr
		,&sin_size))==-1)
		{
			perror("accept");
			continue;
		}

		printf("Server:got connection from %s\n",inet_ntoa(their_addr.sin_addr));

		/* fork a child process to communicate with socket */
		if(!fork())
		{
			/* child process */
			while(1){
				if((n=recv(new_fd,buff,sizeof(buff)-1,0))==-1)
				{
					printf("received EOF\n");
					break;
				}
				buff[n]=0;
				printf("Recv %d bytes: %s\n",n,buff);
			}
			close(new_fd);
		}
	}
	/* wait for all the child process exit */
	while(waitpid(-1,NULL,WNOHANG)>0);
				
	/* resume processor to SIGURG */
	signal(SIGURG,old_sig_urg_handle);
}

void sig_urg(int signo)
{
	int n;
	int new_fd;
	char buff[100];

	printf("SIGURG received\n");
	n=recv(new_fd,buff,sizeof(buff)-1,MSG_OOB);
	buff[n]=0;
	printf("recv %d OOB byte: %s\n",n,buff);
}

