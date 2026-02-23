#include <console/console.h>

void
printAccumulator ()
{
  char hexRender[5] = { 0 };

  int value = 0;
  sc_accumulatorGet (&value);

  mt_gotoXY (RAM_WIDTH + 3, 2);
  write (1, "sc: ", 5);
  printCellValue (value, NOTHING, NOTHING);
  write (1, " hex: ", 7);
  sprintf (hexRender, "%04x", value);
  write (1, hexRender, 4);
}