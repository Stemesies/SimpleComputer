#include <console/console.h>

void
printCommand ()
{

  int sign = 0;
  int command = 0;
  int operand = 0;

  mt_gotoXY (FLAGS_OFFSET_X + 6, INCOUNTER_OFFSET_Y + 1);
  sc_incounterGet (&operand);
  sc_commandDecode (operand, 0, 0, &operand);

  if (operand < 0 || operand >= MEMORY_SIZE)
    {
      write (1, "! + FF : FF", 12);
      return;
    }

  sc_memoryGet (operand, &operand);
  sc_commandDecode (operand, &sign, &operand, &operand);
  char render[12] = { 0 };

  sprintf (render, "  %c %02x : %02x", sign == 1 ? '-' : '+', command,
           operand);
  write (1, render, 12);
}