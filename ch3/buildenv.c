#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int main()
{
  char *argv[]={"showenv",NULL},
    *envp[]={"foo=bar","bar=foo",NULL};

    /* build new environment */
    execve("./showenv",argv,envp);
    perror("exeve failed.");
    return 0;
}
    
