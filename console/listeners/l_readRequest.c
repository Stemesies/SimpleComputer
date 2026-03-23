#include <console/console.h>
#include <include/myReadKey.h>
#include <include/mySimpleComputer.h>

int
l_readRequest (int destAddress)
{
  int wasStopped = 0;
  if (destAddress < 0)
    {
      wasStopped = 1;
      destAddress = -destAddress;
    }
  int *termField = printTerm (destAddress, 1);
  int value = 0;
  int result = 1;

  while (result != 0)
    {
      mt_gotoXY (TERM_OFFSET_X + 5, LOW_OFFSET_Y + 5);
      result = rk_readvalue (&value, 0);
      *termField = ((value << 1) | 1);

      mt_gotoXY (0, COMMAND_LINE_Y);
      mt_delline ();
      mt_setfgcolor (RED);
      switch (result)
        {
        case 0:
          mt_setdefaultcolor ();
          sc_memorySet (destAddress, value);
          if (!wasStopped)
            sc_regSet (REG_TICK_IGNORE, 0);
          l_cellUpdate (destAddress);
          break;
        case 1:
          mt_setdefaultcolor ();
          mt_gotoXY (TERM_OFFSET_X + 5, LOW_OFFSET_Y + 5);
          write (1, "cncld", 6);
          mt_gotoXY (0, COMMAND_LINE_Y);
          return -1;

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
  return 0;
}