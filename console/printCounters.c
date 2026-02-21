#include <console/console.h>

void
printCounters ()
{
  int value = 0;
  sc_incounterGet (&value);
  printCellValue (value);
}