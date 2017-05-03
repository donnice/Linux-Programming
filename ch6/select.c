#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>

#define STDIN 0

/* wait 2.5 sec for stdio */

main()
{
	struct timeval tv;
	fd_set readfds;

	/* set waiting time 2 sec and 500000 mile sec */
	tv.tv_sec = 2;
	tv.tv_usec = 500000;

	FD_ZERO(&readfds);
	FD_SET(STDIN, &readfds);

	/* we set writefds and execeptfds to NULL because
	 * we only want to wait for input
	 * So program will wait for 2.5 sec except that there
	 * is stdio during that time
	 */
	
	select(STDIN+1,&readfds,NULL,NULL,&tv);
	/* test whether STDIN is in readfds */
	if(FD_ISSET(STDIN,&readfds))
	{
		printf("A key was pressed!\n");
	}
	else
	{
		printf("Time out :(/n");
	}
}
