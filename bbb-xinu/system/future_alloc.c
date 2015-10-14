#include <xinu.h>
#include <future.h>

future* future_alloc(int future_flags){
  intmask mask;
  struct futent* fut;

  mask = disable();
  fut = getmem(sizeof(struct futent));
  fut->value = (int *)getmem(sizeof(int));
  fut->flag = future_flags;
  fut->state = FUTURE_EMPTY;
  
  restore(mask);
  return fut;
  
}
