#include <console/console.h>

static char render[6];

void
printCellValue (int encodedCommand, Colors fg, Colors bg)
{
  int sign = 0;
  int command = 0;
  int operand = 0;

  if (sc_commandDecode (encodedCommand, &sign, &command, &operand) != 0)
    {
      printf ("Invalid cell value: 0x%x.\n", encodedCommand);
      return;
    }
  mt_setfgcolor (fg);
  mt_setbgcolor (bg);

  sprintf (render, "%c%02x%02x", sign == 1 ? '-' : '+', command, operand);
  write (1, render, 5);
  mt_setdefaultcolor ();
}