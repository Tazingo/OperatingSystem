#include <xinu.h>
#include <future.h>

syscall future_free(future* future){
  if(future->flag == FUTURE_QUEUE)
  {
  	freemem(future->get_queue,sizeof(struct queue));
  	freemem(future->set_queue,sizeof(struct queue));
  }
  freemem(future->value,sizeof(future->value));
  freemem(future,sizeof(future));
  return OK;
}
