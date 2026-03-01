#include <console/console.h>
#include <stdio.h>

int
main ()
{

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

  init_screen ();

  printMemory ();
  printCell (0, INVERSE, NOTHING);
  printAccumulator ();
  printFlags ();
  printCommand ();
  printDecodedCommand (0);
  printCounters ();

  updateTerm ();
  generateDefault ();
  int ok = 0;
  bc_printbigchar (bc_chartoglyph ('8'), ok, 0, NOTHING, NOTHING);
  ok += 8;
  bc_printbigchar (bc_chartoglyph ('8'), ok, 0, NOTHING, NOTHING);
  ok += 8;
  bc_printbigchar (bc_chartoglyph ('0'), ok, 0, NOTHING, NOTHING);
  ok += 8;
  bc_printbigchar (bc_chartoglyph ('0'), ok, 0, NOTHING, NOTHING);
  ok += 8;
  bc_printbigchar (bc_chartoglyph ('5'), ok, 0, NOTHING, NOTHING);
  ok += 8;
  bc_printbigchar (bc_chartoglyph ('5'), ok, 0, NOTHING, NOTHING);
  ok += 8;
  bc_printbigchar (bc_chartoglyph ('5'), ok, 0, NOTHING, NOTHING);
  ok += 8;
  bc_printbigchar (bc_chartoglyph ('3'), ok, 0, NOTHING, NOTHING);
  ok += 8;
  bc_printbigchar (bc_chartoglyph ('5'), ok, 0, NOTHING, NOTHING);
  ok += 8;
  bc_printbigchar (bc_chartoglyph ('3'), ok, 0, NOTHING, NOTHING);
  ok += 8;
  bc_printbigchar (bc_chartoglyph ('5'), ok, 0, NOTHING, NOTHING);
  ok += 8;

  for (int i = 0; i < 7; i++)
    {
      printTerm (i, i % 2);
      mt_gotoXY (0, COMMAND_LINE_Y);
      sleep (1);
    }

  bc_freeSpace ();

  return 0;
}