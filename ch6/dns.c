#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <netdb.h>
#include <sys/types.h>
#include <netinet/in.h>

int main(int argc,char *argv[])
{
  struct hostent *h; // host name @165

  if(argc!=2) {
    fprintf("usage:getip address\n");

    exit(1);
  }

  /* obtain host info */
  if((h=gethostbyname(argv[1]))==NULL)
    {
      herror("gethostbyname");
      exit(1);
    }

  printf(" Host name:%s\n",h->h_name);
  printf("IP Address:%s\n",inet_ntoa(*((struct in_addr*)h->h_addr)));

  return 0;
}
