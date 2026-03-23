#include <console/console.h>
#include <include/myReadKey.h>

void
l_reset ()
{
  l_incounterUpdate (0);
  printMemory ();
  printAccumulator ();
  printCounters ();
  printFlags ();
  printCommand ();
  printIncounterCell ();
  printSelectedCell ();
}