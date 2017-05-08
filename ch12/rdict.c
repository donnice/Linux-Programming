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

