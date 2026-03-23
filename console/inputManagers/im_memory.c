#include <console/console.h>
#include <include/myReadKey.h>

void
im_memoryLeft ()
{
  if (selectedCell / 10 == RAM_ROWS && selectedCell % RAM_LAST_ROW_LEN == 0)
    {
      moveSelectedCell (selectedCell + RAM_LAST_ROW_LEN - 1);
      return;
    }

  if (selectedCell % 10 == 0)
    moveSelectedCell (selectedCell + RAM_COLUMNS - 1);
  else
    moveSelectedCell (selectedCell - 1);
}

void
im_memoryRight ()
{
  if (selectedCell / 10 == RAM_ROWS
      && selectedCell % RAM_LAST_ROW_LEN == RAM_LAST_ROW_LEN - 1)
    {
      moveSelectedCell (selectedCell - RAM_LAST_ROW_LEN + 1);
      return;
    }

  if (selectedCell % 10 == 9)
    moveSelectedCell (selectedCell - RAM_COLUMNS + 1);
  else
    moveSelectedCell (selectedCell + 1);
}

void
im_memoryUp ()
{

  if (selectedCell / RAM_COLUMNS == 0)
    {
      if (selectedCell % RAM_COLUMNS >= RAM_LAST_ROW_LEN)
        moveSelectedCell ((RAM_ROWS - 1) * RAM_COLUMNS
                          + (selectedCell % RAM_COLUMNS));
      else
        moveSelectedCell ((RAM_ROWS)*RAM_COLUMNS
                          + (selectedCell % RAM_COLUMNS));
    }
  else
    moveSelectedCell (selectedCell - RAM_COLUMNS);
}

void
im_memoryDown ()
{
  if (selectedCell % RAM_COLUMNS >= RAM_LAST_ROW_LEN
      && selectedCell / RAM_COLUMNS == RAM_ROWS - 1)
    {
      moveSelectedCell (selectedCell % RAM_COLUMNS);
      return;
    }

  if (selectedCell / RAM_COLUMNS == RAM_ROWS)
    {
      moveSelectedCell (selectedCell % RAM_COLUMNS);
    }
  else
    moveSelectedCell (selectedCell + RAM_COLUMNS);
}