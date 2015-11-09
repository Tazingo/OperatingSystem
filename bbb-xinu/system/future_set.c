#include <xinu.h>
#include <future.h>

syscall future_set(future *fut, int *value){
  intmask mask;
  mask = disable();

  if(fut->flag == FUTURE_EXCLUSIVE || 
     fut->flag == FUTURE_SHARED)
  {

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

  }

  if(fut->flag == FUTURE_QUEUE){
    if(emptyq(fut->get_queue))
    {
      enq(getpid(),fut->set_queue);
      *(fut->value) = *value;
      suspend(getpid());
    }
    else
    {
      pid32 res;
      res = deq(fut->get_queue);
      *(fut->value) = *value;
      resume(res);
    }
  }
  restore(mask);
  return OK;
}
