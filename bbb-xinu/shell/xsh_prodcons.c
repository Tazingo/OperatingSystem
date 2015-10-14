#include <xinu.h>
#include <string.h>
#include <prodcons.h>
#include <future.h>

int n;                 //Definition for global variable 'n'
/*Now global variable n will be on Heap so it is accessible all the processes i.e. consume and produce*/
sid32 consumed, produced; 
shellcmd xsh_prodcons(int nargs, char *args[])
{
  //Argument verifications and validations
  //
  if (nargs == 2 && strncmp(args[1], "--help", 7) == 0) {
    printf("Usage: %s <Integer>\n\n", args[0]);
    return OK;
  }
  if(nargs == 2 && strncmp(args[1], "-f", 7) == 0){
    future *f1, *f2, *f3;
 
    f1 = future_alloc(FUTURE_EXCLUSIVE);
    f2 = future_alloc(FUTURE_EXCLUSIVE);
    f3 = future_alloc(FUTURE_EXCLUSIVE);
 
    resume( create(future_cons, 1024, 20, "fcons1", 1, f1) );
    resume( create(future_prod, 1024, 20, "fprod1", 1, f1) );
    resume( create(future_cons, 1024, 20, "fcons2", 1, f2) );
    resume( create(future_prod, 1024, 20, "fprod2", 1, f2) );
    resume( create(future_cons, 1024, 20, "fcons3", 1, f3) );
    resume( create(future_prod, 1024, 20, "fprod3", 1, f3) );
    return 0;
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
  consumed = semcreate(1);
  produced = semcreate(0);
  
  //create the process producer and consumer and put them in ready queue.
  //Look at the definations of function create and resume in exinu/system folder for reference.      
  resume( create(producer, 1024, 20, "producer", 1, count) );
  resume( create(consumer, 1024, 20, "consumer", 1, count) );
}
