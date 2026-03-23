#include <console/console.h>
#include <include/myReadKey.h>

void
l_cellUpdate (int cell)
{
  printCell (cell, NOTHING, NOTHING);

  if (cell == selectedCell)
    printSelectedCell ();

  else if (cell == incounterCell)
    printIncounterCell ();
}