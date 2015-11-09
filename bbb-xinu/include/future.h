#ifndef _FUTURE_H_
#define _FUTURE_H_
 
/* define states */
#define FUTURE_EMPTY  0
#define FUTURE_WAITING   1         
#define FUTURE_VALID   2         

/* modes of operation for future*/
#define FUTURE_EXCLUSIVE  1
#define FUTURE_SHARED     2    
#define FUTURE_QUEUE      3   

typedef struct queue
{
	pid32 qkey;
	struct queue *qnext;
} queue;

extern pid32 enq(pid32, queue*);
extern pid32 deq(queue*);
extern int32 emptyq(queue*);

typedef struct futent
{
  int *value;
  int flag;
  int state;         
  pid32 pid;
  queue *set_queue;
  queue *get_queue;
} future;



/* Interface for system call */
future* future_alloc(int future_flags);
syscall future_free(future*);
syscall future_get(future*, int*);
syscall future_set(future*, int*);

uint32 future_prod(future *fut);
uint32 future_cons(future *fut);
 
#endif 
