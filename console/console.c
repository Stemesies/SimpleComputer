#include <console/console.h>
#include <stdio.h>

int
main ()
{

  init_screen ();

  if (!isatty (STDOUT_FILENO))
    {
      mt_setfgcolor (RED);
      write (1, "Not opened in terminal.\n", 25);
      mt_setdefaultcolor ();
      return -1;
    }

  int width = 0;
  int height = 0;
  mt_getscreensize (&height, &width);

  mt_gotoXY (0, 0);
  if (width <= SCREEN_WIDTH)
    {
      mt_setfgcolor (RED);
      write (1, "Screen width is too small.\n", 27);
      mt_setdefaultcolor ();
      return -1;
    }

  if (height <= SCREEN_HEIGHT)
    {
      mt_setfgcolor (RED);
      write (1, "Screen height is too small.\n", 28);
      mt_setdefaultcolor ();
      return -1;
    }

  init_memoryBlock ();
  init_accumulatorBlock ();
  init_flagsBlock ();
  init_incounterBlock ();
  init_commandBlock ();
  init_detailedCellBlock ();
  init_cacheBlock ();
  init_termBlock ();
  init_keybindsBlock ();

  printMemory ();
  printCell (0, INVERSE, NOTHING);
  printAccumulator ();
  printFlags ();
  printCommand ();
  printDecodedCommand (0);
  printCounters ();

  updateTerm ();

  for (int i = 0; i < 7; i++)
    {
      printTerm (i, i % 2);
      mt_gotoXY (0, LOW_OFFSET_Y + 7);
      sleep (1);
    }

  return 0;
}