#include <stdio.h>
#include <rpc/rpc.h>

#include "rdict.h"

extern CLIENT *handle;
/* temp store return data */
static int *ret;

int initw()
{
	ret = initw_1(0,handle);
	return ret==0? 0:*ret;
}

int insertw(const char* word)
{
	char **arg;
	arg = &word;
	ret = insertw_1(arg,handle);
	return ret==0? 0:*ret;
}

int deletew(const char* word)
{
	char **arg;
	arg = (char**)&word;

	ret=deletew_1(arg,handle);
	return ret==0?0:*ret;
}

int lookupw(const char* word)
{
	char **arg;
	arg = &word;
	ret = lookupw_1(arg,handle);
	return ret==0? 0: *ret;
}
