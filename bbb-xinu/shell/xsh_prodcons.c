#include <xinu.h>
#include <string.h>
#include <prodcons.h>

int n;                 //Definition for global variable 'n'
/*Now global variable n will be on Heap so it is accessible all the processes i.e. consume and produce*/

shellcmd xsh_prodcons(int nargs, char *args[])
{
	//Argument verifications and validations
	//
	if (nargs == 2 && strncmp(args[1], "--help", 7) == 0) {
		printf("Usage: %s <Integer>\n\n", args[0]);
		return OK;
	}
	int count = 2000;
	char *chptr;
	char ch;
	if(nargs == 2){
	  chptr = args[1];
	  ch = *chptr++;
	  count = 0;
	  while(ch != NULLCH){
	    if((ch<'0') || (ch > '9')){
	      fprintf(stderr, "%s is not a valid integer.\n",args[0]);
	      return 1;
	    }
	    count = 10*count + (ch - '0');
	    ch = *chptr++;
	  }
	}
	if(nargs > 2){
	  fprintf(stderr, "%s: incorrect argument\n", args[0]);
	  fprintf(stderr, "Try '%s --help' for more information\n",
		  args[0]);
	  return SYSERR;
	}


	//create the process producer and consumer and put them in ready queue.
	//Look at the definations of function create and resume in exinu/system folder for reference.      
    resume( create(producer, 1024, 20, "producer", 1, count) );
    resume( create(consumer, 1024, 20, "consumer", 1, count) );
}
