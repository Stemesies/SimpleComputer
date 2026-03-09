#include <console/console.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

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

int
main (int argc, char *argv[])
{
  srand (time (NULL));

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
  mt_clrscr ();
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

  switch (bc_load (argc > 1 ? argv[1] : "font.bin"))
    {
    case -3:
      mt_setfgcolor (RED);
      write (1, "No font file found.\n", 21);
      mt_setdefaultcolor ();
      return -1;
    case 0:
      break;
    default:
      mt_setfgcolor (RED);
      write (1, "Error during parsing font file.\n", 33);
      mt_setdefaultcolor ();
      return -1;
    }

  init_screen ();

  for (int i = 0; i < MEMORY_SIZE; i++)
    {
      sc_memorySet (i, (int)(rand () % 32768));
    }

  printMemory ();
  printAccumulator ();
  printFlags ();
  printCommand ();
  printCounters ();
  updateTerm ();

  for (int i = 0; i < 7; i++)
    {
      printTerm (i, i % 2);
      setSelectedCell ((int)(rand () % MEMORY_SIZE));
      mt_gotoXY (0, COMMAND_LINE_Y);
      sleep (1);
    }

  bc_freeSpace ();

  return 0;
}