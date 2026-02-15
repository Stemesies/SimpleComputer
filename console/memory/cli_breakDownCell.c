#include <console/console.h>

void
cli_breakDownCell (int address)
{
  int value = 0;

  if (sc_memoryGet (address, &value) != 0)
    {
      printf ("INV:%d", address);
      return;
    }

  cli_printDecodedCommand (value);
  putchar ('\n');
  cli_breakdownCommand (value);
}