/* rdict.x RPC explanation */
const MAXWORD = 50;
const DICTSIZ = 100;

/*
 * RDICTPROG including insert, del, lookup
 */

program RDICTPROG
{
	version RDICTVERS
	{
		int INITW(void) = 1;
		int INSERTW(string) = 2;
		int DELETEW(string) = 3;
		int LOOKUPW(string) = 4;
	}=1;
}=0x30090949;
