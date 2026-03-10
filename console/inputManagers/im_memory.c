#include <console/console.h>
#include <include/myReadKey.h>
#include <include/mySimpleComputer.h>
#include <include/myTerm.h>
#include <unistd.h>

#define STRINGIFY(x) #x

int selectedCell = 0;

int
getSelectedCell ()
{
  return selectedCell;
}

void
setSelectedCell (int addr)
{
  printCell (selectedCell, RESET, NOTHING);
  selectedCell = addr;
  printCell (selectedCell, INVERSE, NOTHING);
  printBigCell ();
  printDecodedCommand ();
}

void
im_memoryLeft ()
{
  if (selectedCell / 10 == RAM_ROWS && selectedCell % RAM_LAST_ROW_LEN == 0)
    {
      setSelectedCell (selectedCell + RAM_LAST_ROW_LEN - 1);
      return;
    }

  if (selectedCell % 10 == 0)
    setSelectedCell (selectedCell + RAM_COLUMNS - 1);
  else
    setSelectedCell (selectedCell - 1);
}

void
im_memoryRight ()
{
  if (selectedCell / 10 == RAM_ROWS
      && selectedCell % RAM_LAST_ROW_LEN == RAM_LAST_ROW_LEN - 1)
    {
      setSelectedCell (selectedCell - RAM_LAST_ROW_LEN + 1);
      return;
    }

  if (selectedCell % 10 == 9)
    setSelectedCell (selectedCell - RAM_COLUMNS + 1);
  else
    setSelectedCell (selectedCell + 1);
}

void
im_memoryUp ()
{

  if (selectedCell / RAM_COLUMNS == 0)
    {
      if (selectedCell % RAM_COLUMNS >= RAM_LAST_ROW_LEN)
        setSelectedCell ((RAM_ROWS - 1) * RAM_COLUMNS
                         + (selectedCell % RAM_COLUMNS));
      else
        setSelectedCell ((RAM_ROWS)*RAM_COLUMNS
                         + (selectedCell % RAM_COLUMNS));
    }
  else
    setSelectedCell (selectedCell - RAM_COLUMNS);
}

void
im_memoryDown ()
{
  if (selectedCell % RAM_COLUMNS >= RAM_LAST_ROW_LEN
      && selectedCell / RAM_COLUMNS == RAM_ROWS - 1)
    {
      setSelectedCell (selectedCell % RAM_COLUMNS);
      return;
    }

  if (selectedCell / RAM_COLUMNS == RAM_ROWS)
    {
      setSelectedCell (selectedCell % RAM_COLUMNS);
    }
  else
    setSelectedCell (selectedCell + RAM_COLUMNS);
}

void
im_memoryWrite ()
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
      setSelectedCell (selectedCell);
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
      setSelectedCell (selectedCell);
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
    case -11:
      write (1, "Command validator: command out of bounds.", 42);
      break;
    default:
      write (1, "Unknown error", 14);
    }
  mt_setdefaultcolor ();
}