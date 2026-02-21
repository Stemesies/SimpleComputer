#include <console/console.h>

void
printCell (int address)
{
  int value = 0;

  if (sc_memoryGet (address, &value) != 0)
    {
      printf ("INV:%d", address);
      return;
    }

  printCellValue (value);
}