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

  mt_gotoXY (0, COMMAND_LINE_Y);
  mt_delline ();

  if (result == 0)
    {
      sc_memorySet (selectedCell, value);
      moveSelectedCell (selectedCell);
      l_incounterUpdate (0);
      printCell (selectedCell, BLACK, GREEN);
      return;
    }

  printCell (selectedCell, BLACK, RED);

  if (result == 1)
    moveSelectedCell (selectedCell);
  else
    invalidCellExplain (result);
}