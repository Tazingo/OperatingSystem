#include <xinu.h>
#include <future.h>

syscall future_get(future* fut,int* value){
  intmask mask;
  mask = disable();

  if(fut->state == FUTURE_WAITING){
    restore(mask);
    return SYSERR;
  }

  if(fut->state == FUTURE_VALID){
    fut->state = FUTURE_EMPTY;
    *value = &(fut->value);
    restore(mask);
    return OK;
  }else if(fut->state == FUTURE_EMPTY){
    fut->state = FUTURE_WAITING;
    fut->pid = getpid();
    resched();
    *value = &(fut->value);
  }
  restore(mask);
  return OK;
}
