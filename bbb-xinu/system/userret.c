/* userret.c - userret */

#include <xinu.h>

/*------------------------------------------------------------------------
 *  userret  -  Called when a process returns from the top-level function
 *------------------------------------------------------------------------
 */
void	userret(void)
{
	struct procent *prptr;
	prptr = &proctab[getpid()];
	printf("Process %d exit, max stack size: %8d\n",(int)getpid(),prptr->prstklen);
	kill(getpid());			/* Force process to exit */
}
