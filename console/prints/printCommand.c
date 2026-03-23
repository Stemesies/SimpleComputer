#include "include/mySimpleComputer.h"
#include <console/console.h>
#include <stdio.h>

void
printCommand ()
{

  int sign = 0;
  int command = 0;
  int operand = 0;

  mt_gotoXY (FLAGS_OFFSET_X + 6, INCOUNTER_OFFSET_Y + 1);
  sc_incounterGet (&operand);
  sc_memoryGet (operand, &operand);

  if (sc_commandValidate (operand) != 0)
    {
      write (1, "! + FF : FF", 12);
      return;
    }

  sc_commandDecode (operand, &sign, &command, &operand);

  char render[20] = { 0 };

  sprintf (render, "  %c %02x : %02x", sign == 1 ? '-' : '+', command,
           operand);
  write (1, render, 20);
}