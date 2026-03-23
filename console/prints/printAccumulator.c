#include <console/console.h>
#include <include/utils.h>
void
printAccumulator ()
{
  int value = 0;
  sc_accumulatorGet (&value);

  mt_gotoXY (RAM_WIDTH + 3, 2);
  write (1, "sc: ", 5);
  printCellValue (value, NOTHING, NOTHING);
  writef (" hex: %04x", value);
}