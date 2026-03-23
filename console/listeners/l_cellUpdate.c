#include <console/console.h>
#include <include/myReadKey.h>
#include <include/mySimpleComputer.h>

void
l_cellUpdate (int cell)
{
  printCell (cell, NOTHING, NOTHING);

  if (cell == selectedCell)
    printSelectedCell ();

  else if (cell == incounterCell)
    printIncounterCell ();
}