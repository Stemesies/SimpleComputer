#include <console/console.h>

void
printCell (int address, Colors fg, Colors bg)
{
  int value = 0;

  if (sc_memoryGet (address, &value) != 0)
    {
      mt_setfgcolor (BRIGHT_WHITE);
      mt_setbgcolor (RED);
      printf ("INV:%d", address);
      mt_setdefaultcolor ();
      return;
    }

  mt_gotoXY (2 + (address % RAM_COLUMNS) * 6, 2 + (address / RAM_COLUMNS));
  printCellValue (value, fg, bg);
}