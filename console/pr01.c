#include <console/console.h>
#include <stdio.h>

int
main ()
{
  init_screen ();
  init_memoryBlock ();
  init_accumulatorBlock ();
  init_flagsBlock ();
  init_incounterBlock ();

  printMemory ();
  printCell (0, INVERSE, NOTHING);
  printAccumulator ();
  printFlags ();
  scanf ("%s", 0);

  return 0;
}