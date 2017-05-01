#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/wait.h>

#define MYPORT 4000

/* max unaccept link */
#define BACKLOG 10

main()
{
  /* listen at sock_fd, new_fd get new connect */
  int sock_fd,new_fd;
  /* own address */
  struct sockaddr_in my_addr;

  /* target address */
  struct sockaddr_in their_addr;

  int sin_size;

  if((sock_fd=socket(AF_INET,SOCK_STREAM,0))==-1)
    {
      perror("socket");
      exit(1);
    }

  /* host endian */
  my_addr.sin_family=AF_INET;

  /* internet endian */
  my_addr.sin_port = htons(MYPORT);

  /* ip to s_addr */
  my_addr.sin_addr.s_addr=INADDR_ANY;

  /* bzero the rest */
  bzero(&(my_addr.sin_zero),8);

  if(bind(sock_fd,(struct sockaddr *)&my_addr,sizeof(struct sockaddr)) == -1)
    {
      perror("bind");
      exit(1);
    }

  if(listen(sock_fd,BACKLOG)==-1)
    {
      perror("listen");
      exit(1);
    }

  while(1)
    {
      sin_size=sizeof(struct sockaddr_in);
  
      if((new_fd=accept(sock_fd,(struct sockaddr *)&their_addr,&sin_size))==-1)
	{
	  perror("accept");
	  continue;
	}

      printf("Server:got connection from %s\n",inet_ntoa(their_addr.sin_addr));
      /* build a child process to communicate with built sock */
      if(!fork()) {
	if(send(new_fd,"Hello,world!\n",14,0)==-1)
	  {
	    perror("send");
	    close(new_fd);
	    exit(0);
	  }
	close(new_fd);
      }
    }

  /* wait for child process to exit */
  while(waitpid(-1,NULL,WNOHANG)>0);
}

      
