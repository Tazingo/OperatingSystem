#include <xinu.h>
#include <prodcons.h>

void consumer(int count)
{
	//Code to consume values of global variable 'n' until the value
	//of n is less than or equal to count
	//print consumed value e.g. consumed : 8
  int i = 0;
  while(i< count)
  {
    wait(produced);
    printf("consumed: %d\n", n);
    i++;
    signal(consumed);
  }
}
