#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>

#define MAXWORD 50
int nextin(char* cmd, char* word);
int initw();
int insertw(const char* word);
int deletew(const char* word);
int lookupw(const char* word);

int main(int argc, char* agrv[])
{
	char word[MAXWORD+1];
	char cmd;
	/* word len */
	int wrdlen;

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
				printf("Dictionary initialized to empty.\n");
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
					printf("%s was found.\n",word);
				} else {
					printf("%s was not found.\n",word);
				}
				break;
			case 'q':
				printf("program quits \n");
				exit(0);
			default:
				printf("command %c invalid.\n",cmd);
				break;
		}
	}
}

/*
 * nextin: read input and arg
 */
int nextin(char* cmd, char* word)
{
	int i,ch;

	ch = getc(stdin);
	while(isspace(ch))
	{
		ch = getc(stdin);
	}
	if(ch == EOF)
	{
		return -1;
	}
	*cmd = (char)ch;
	ch = getc(stdin);
	while(isspace(ch))
	{
		ch = getc(stdin);
	}
	if(EOF==ch)
	{
		return -1;
	}
	if('\n'==ch)
	{
		return 0;
	}
	i=0;
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
	*word++=0;
	return i;
}




