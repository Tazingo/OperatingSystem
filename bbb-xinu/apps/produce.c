#include <xinu.h>
#include <prodcons.h>

void producer(int count)
{
	//Code to produce values less than equal to count, 
	//produced value should get assigned to global variable 'n'.
	//print produced value e.g. produced : 8
  int i = 0;
  while(i< count)
  {
    wait(consumed);
    n = i;
    printf("produced: %d\n", n);    
    i++;
    signal(produced);
  } 
}
