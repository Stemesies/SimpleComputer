#include <console/console.h>

void
printAccumulator ()
{
  int value = 0;
  sc_accumulatorGet (&value);
  printCellValue (value);
}