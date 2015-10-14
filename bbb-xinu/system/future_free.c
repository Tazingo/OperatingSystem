#include <xinu.h>
#include <future.h>

syscall future_free(future* future){
  freemem(future->value,sizeof(future->value));
  freemem(future,sizeof(future));
  return OK;
}
