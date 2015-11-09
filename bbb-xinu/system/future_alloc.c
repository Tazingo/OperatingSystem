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

  if(future_flags == FUTURE_QUEUE){
    fut->set_queue = (struct queue *)getmem(sizeof(struct queue));
    fut->set_queue->qkey = 0;
    fut->set_queue->qnext = NULL;
    fut->get_queue = (struct queue *)getmem(sizeof(struct queue));
    fut->get_queue->qkey = 0;
    fut->get_queue->qnext = NULL;
  }

  restore(mask);
  return fut;
  
}

pid32 enq(
  pid32 pid,
  queue* q
){
  intmask mask;
  mask = disable();
  
  if(q->qkey == 0){
      q->qkey = pid;
      restore(mask);
      return pid;
  }

  struct queue *curr, *prev;
  curr = q->qnext;
  prev = q;
  while(curr!=NULL){
    prev = curr;
    curr = curr->qnext;
  }
  prev->qnext = getmem(sizeof(struct queue));
  prev->qnext->qkey = pid;
  prev->qnext->qnext = NULL;
  restore(mask);
  return pid;
}


pid32 deq(queue* q){
  intmask mask;
  mask = disable();

  if(q->qkey == 0){
    restore(mask);
    return 0;
  }
  pid32 r;
  r = q->qkey;
  if(q->qnext != NULL){
    struct queue *n;
    q->qkey = q->qnext->qkey;
    n = q->qnext;
    q->qnext = n->qnext;
    freemem(n,sizeof(struct queue));
  }else{
    q->qkey = 0;
  }
  restore(mask);
  return r;
}

int32 emptyq(queue* q){
  if(q->qkey == 0){
    return 1;
  }else{
    return 0;
  }
}