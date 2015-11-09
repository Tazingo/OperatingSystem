#include <xinu.h>
#include <string.h>

shellcmd xsh_free(int nargs, char *args[])
{
  //Argument verifications and validations
  //
  if (nargs == 2 && strncmp(args[1], "--help", 7) == 0) {
    printf("Usage: %s for 9.1\n", args[0]);
    return OK;
  }

  struct memblk *memptr;
  for (memptr=memlist.mnext; memptr!=NULL;memptr = memptr->mnext) {
    kprintf("Address: 0x%08X, length: %u\n",
    (uint32)memptr, memptr->mlength);
  }
  return 0;
}
