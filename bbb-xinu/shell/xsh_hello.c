/* Assignment 1
   xsh_hello
 */
#include <xinu.h>
#include <stdio.h>

shellcmd xsh_hello(int nargs, char *args[])
{
  if(nargs > 1){
    printf("Hello %s, Welcome to the world of Xinu!!",args[1]);
  }
  printf("\n");
  return 0;
}
