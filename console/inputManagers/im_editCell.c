#include <console/console.h>
#include <include/myReadKey.h>

void
im_editCell ()
{
  int value = 0;
  printCell (selectedCell, GREEN, GREEN);
  mt_gotoXY (2 + (selectedCell % RAM_COLUMNS) * 6,
             2 + (selectedCell / RAM_COLUMNS));

  mt_setbgcolor (BLACK);
  int result = rk_readvalue (&value, 0);
  mt_setdefaultcolor ();

  if (result == 0)
    {
      sc_memorySet (selectedCell, value);
      moveSelectedCell (selectedCell);
      printCell (selectedCell, BLACK, GREEN);
      printTerm (selectedCell, 1);
      return;
    }

  printCell (selectedCell, BLACK, RED);
  mt_gotoXY (0, COMMAND_LINE_Y);
  mt_delline ();
  mt_setfgcolor (RED);
  switch (result)
    {
    case 1:
      moveSelectedCell (selectedCell);
      break;

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
    default:
      write (1, "Unknown error", 14);
    }
  mt_setdefaultcolor ();
}