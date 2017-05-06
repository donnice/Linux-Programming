#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>

#define MAXWORD 50

#define DICTSIZ 100

char dict[DICTSIZ][MAXWORD+1];

int nwords=0;
int nextin(char* cmd,char* word);
int initw();
int insertw(const char* word);
int deletew(const char* word);
int lookupw(const char* word);

int main(int argc, char* argv[])
{
	/* get var from cmd line */
	char word[MAXWORD+1];
	char cmd;

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
				printf("Dictionary initalized to empty.\n");
				break;
			case 'i':
				insert(word);
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
				printf("command %c invalid. \n",cmd);
				break;
		}
	}
}

/*
 * Read input cmd and parameter
 */

int nextin(char* cmd, char* word)
{
	int i, ch;
	
	ch=getc(stdin);
	while(isspace(ch))
	{
		ch=getc(stdin);
	}
	if(ch==EOF)
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
		ch=getc(stdin);
	}
	*word++=0;
	return i;
}

/*
 * Initialize dict
 */
int initw()
{
	nwords=0;
	return 1;
}

int insertw(const char* word)
{
	strcpy(dict[nwords],word);
	nwords++;
	return nwords;
}

int lookupw(const char* word)
{
	int I;
	for(I=0; nwords > I; I++)
	{
		if(0 == strcmp(word,dict[I]))
		{
			return 1;
		}
	}
	return 0;
}
