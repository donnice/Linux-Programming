#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>

/* max word */
#define MAXWORD 50
/* max dict size */
#define DICTSIZ 100
/* dict array */
char dict[DICTSIZ][MAXWORD+1];

int nwords = 0;
int nextin(char* cmd, char* word);
int initw();
int insertw(const char* word);
int deletew(const char* word);
int lookupw(const char* word);

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

int deletew(const char* word)
{
	int i;
	for(i=0;i<nwords;i++)
	{
		if(0==strcmp(word,dict[i]))
		{
			nwords--;
			strcpy(dict[i],dict[nwords]);
			return 1;
		}
	}
	return 0;
}

int lookupw(const char* word)
{
	int i;
	for(i = 0; nwords > i;i++)
	{
		if(0 == strcmp(word,dict[i]))
		{
			return 1;
		}
	}
	return 0;
}
