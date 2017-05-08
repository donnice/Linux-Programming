/* include init_1,insert_1, delete_1,lookup_1 */
#include <rpc/rpc.h>
#include "rdict.h"

static int retcode;

/*
 * server side interface: insertw 
 */
int *insertw_1_svc(char**w, struct svc_req *rqstp)
{
	retcode = insertw(*w);
	return &retcode;
}

int *initw_1_svc(void *p, struct svc_req *rqstp)
{
	retcode = initw();
	return &retcode;
}

int *deletew_1_svc(char **w, struct svc_req *rqstp)
{
	retcode = deletew(*w);
	return &retcode;
}

int *lookupw_1_svc(char **w, struct svc_req *rqstp)
{
	retcode = lookupw(*w);
	return &retcode;
}

