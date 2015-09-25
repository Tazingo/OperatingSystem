#include <xinu.h>

shellcmd xsh_reset(int nargs, char *args[])
{
  volatile uint32 *resetctrl = (volatile uint32 *) 0x44E00F00;
  *resetctrl = 0x01;
}
