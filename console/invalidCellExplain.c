#include <console/console.h>

void
invalidCellExplain (int resultCode)
{
  mt_gotoXY (0, COMMAND_LINE_Y);
  mt_setfgcolor (RED);
  switch (resultCode)
    {
    case -20:
      write (1, "Illegal cell format and/or illegal symbols.", 44);
      break;
    case -10:
      write (1, "Illegal sign. Allowed only '+' or '-'.", 39);
      break;
    case -2:
      write (1, "Command field overflow.", 24);
      break;
    case -3:
      write (1, "Operand field overflow.", 24);
      break;
    case -5:
      write (1, "Invalid value 'negative zero' ", 31);
      break;
    default:
      write (1, "Unknown error", 14);
      break;
    }
  mt_setdefaultcolor ();
}