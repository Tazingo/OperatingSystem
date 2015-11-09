#include <xinu.h>
#include <future.h>

syscall future_get(future* fut,int* value){
  intmask mask;
  mask = disable();
  if(fut->flag == FUTURE_EXCLUSIVE){

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
  }

  if(fut->flag == FUTURE_SHARED){
    if(fut->state == FUTURE_VALID){
      fut->state = FUTURE_EMPTY;
      *value = &(fut->value);
      restore(mask);
      return OK;
    }
    else if(fut->state == FUTURE_EMPTY || 
	    fut->state == FUTURE_WAITING)
    {
      fut->state = FUTURE_WAITING;
      fut->pid = getpid();
      resched();
      *value = &(fut->value);
    }
  }

  if(fut->flag == FUTURE_QUEUE)
  {
    if(emptyq(fut->set_queue))
    {
      enq(getpid(),fut->get_queue);
      suspend(getpid());
      *value = &(fut->value);
    }
    else
    { 
      pid32 res;
      res = deq(fut->set_queue);
      resume(res);
      *value = &(fut->value);
    }
  }
  restore(mask);
  return OK;
}
