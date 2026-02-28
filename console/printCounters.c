#include <console/console.h>

void
printCounters ()
{
  int value = 0;
  sc_incounterGet (&value);

  mt_gotoXY (RAM_WIDTH + 3, INCOUNTER_OFFSET_Y + 1);
  write (1, "T: 00     IC: ", 15);
  printCellValue (value, NOTHING, NOTHING);
}