#include <sys/types.h>
#include <signal.h>
#include <unistd.h>
#include <syslog.h>

#define MAXFD 64

void daemon_init(const char* pname,int facility)
{
  int i;
  pid_t pid;

  /* fork stop parent */
  if(pid=fork())
    exit(0);
  /* set first child process */
  setsid();

  signal(SIGNUP,SIG_IGN);
  /* fork first child process */
  if(pid=fork())
    exit(0);
  /* second child process */
  daemon_proc = 1;
  /* set work directory as "/" */
  chdir("/");
  /* delete mask code */
  unmask(0);
  /* close all file */
  for(i=0;i<MAXFD;i++)
    close(i);
  openlog(pname,LOG_PID,facility);
}
  
