#include <xinu.h>
#include <future.h>

syscall future_set(future *fut, int *value){
  intmask mask;
  mask = disable();

  *(fut->value) = *value;
  if(fut->state == FUTURE_VALID){
    restore(mask);
    return SYSERR;
  }
  if(fut->state == FUTURE_EMPTY){
    fut->state = FUTURE_VALID;
  }else if(fut->state == FUTURE_WAITING){
    fut->state = FUTURE_VALID;
    ready(fut->pid);
  }
  restore(mask);
  return OK;
}
