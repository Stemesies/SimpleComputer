#include "include/myTerm.h"
#include <console/console.h>

void
forcePrintIncounterCell ()
{
  if (incounterCell >= MEMORY_SIZE)
    return;

  if (incounterCellIsIdling != 0)
    printCell (incounterCell, BLACK, RED);
  else
    printCell (incounterCell, BLACK, GREEN);
}

void
printIncounterCell ()
{
  if (incounterCell == selectedCell)
    return;
  forcePrintIncounterCell ();
}

void
moveIncounterCell ()
{
  static int lastIncounterCell = 0;

  if (lastIncounterCell != selectedCell && lastIncounterCell < MEMORY_SIZE)
    printCell (lastIncounterCell, RESET, RESET);

  printIncounterCell ();

  lastIncounterCell = incounterCell;
}

void
printSelectedCell ()
{
  printCell (selectedCell, INVERSE, NOTHING);
  printBigCell ();
  printDecodedCommand ();
}

void
hideSelectedCell ()
{
  printCell (selectedCell, RESET, RESET);

  if (selectedCell != incounterCell)
    return;

  forcePrintIncounterCell ();
}

void
moveSelectedCell (int to)
{
  hideSelectedCell ();
  selectedCell = to;
  printSelectedCell ();
}