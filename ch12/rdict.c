#include <rpc/rpc.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>

#include "rdict.h"

#define MAXWORD 50
#define RMACHINE "localhost"

/* rdict.c including main and nextin */

CLIENT *handle;
int nextin(char* cmd, char* word);
int initw();
int insertw(const char* word);
int deletew(const char* word);
int lookupw(const char* word);

int main(int argc, char* argv[])
{
	char word[MAXWORD+1];
	char cmd;

	int wrdlen;

	handle = clnt_create(RMACHINE, RDICTPROG,RDICTVERS,"tcp");
	if(0 == handle)
	{
		printf("Could not contact remote program.\n");
		exit(1);
	}
	while(1)
	{
		wrdlen = nextin(&cmd,word);
		if(wrdlen < 0)
		{
			exit(0);
		}
		switch(cmd)
		{
			case 'I':
				initw();
				printf("Dictionary initalized to empty. \n");
				break;
			case 'i':
				insertw(word);
				printf("%s inserted.\n",word);
				break;
			case 'd':
				if(deletew(word))
				{
					printf("%s deleted.\n",word);
				} else {
					printf("%s not found.\n",word);
				}
				break;
			case 'l':
				if(lookupw(word))
				{
					printf("%s was found!\n",word);
				} else {
					printf("%s was not found.\n",word);
				}
				break;
			case 'q':
				printf("program quits \n");
				exit(0);
			default:
				printf("command %c invalid. \n",cmd);
				break;
		}
	}
	clnt_destroy(handle);
}

int nextin(char* cmd, char* word)
{
	int i, ch;

	ch = getc(stdin);
	while(isspace(ch))
	{
		ch = getc(stdin);
	}
	if(EOF == ch)
	{
		return -1;
	}
	i = 0;
	while(!isspace(ch))
	{
		if(MAXWORD < ++i)
		{
			printf("error:word too long\n");
			exit(1);
		}
		*word++=ch;
		ch = getc(stdin);
	}
	*word++ = 0;
	return i;
}
