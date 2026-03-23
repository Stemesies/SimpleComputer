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

        default:
          invalidCellExplain (result);
          break;
        }
      mt_setdefaultcolor ();
    }
  return 0;
}