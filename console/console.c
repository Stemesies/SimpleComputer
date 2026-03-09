#include "include/mySimpleComputer.h"
#include "include/myTerm.h"
#include <console/console.h>
#include <include/myReadKey.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

void
loadFont (char *font)
{
  switch (bc_load (font))
    {
    case -3:
      mt_setfgcolor (RED);
      write (1, "No font file found.\n", 21);
      mt_setdefaultcolor ();
      exit (-1);
    case 0:
      break;
    default:
      mt_setfgcolor (RED);
      write (1, "Error during parsing font file.\n", 33);
      mt_setdefaultcolor ();
      exit (-1);
    }
}

void
checkTty ()
{
  if (!isatty (STDOUT_FILENO))
    {
      mt_setfgcolor (RED);
      write (1, "Not opened in terminal.\n", 25);
      mt_setdefaultcolor ();
      exit (-1);
    }
}

void
checkTerminalSize ()
{
  int width = 0;
  int height = 0;
  mt_getscreensize (&height, &width);
  if (width <= SCREEN_WIDTH)
    {
      mt_setfgcolor (RED);
      write (1, "Screen width is too small.\n", 27);
      mt_setdefaultcolor ();
      exit (-1);
    }

  if (height <= SCREEN_HEIGHT)
    {
      mt_setfgcolor (RED);
      write (1, "Screen height is too small.\n", 28);
      mt_setdefaultcolor ();
      exit (-1);
    }
}

void
testKeys ()
{
  Keys key = K_0;
  while (1)
    {
      rk_readkey (&key);
      printf ("You typed: %d | '%c'\n", key, key);
    }
  exit (0);
}

int
main (int argc, char *argv[])
{
  if (argc > 1 && strcmp (argv[1], "--test-keys") == 0)
    {
      testKeys ();
    }

  srand (time (NULL));

  checkTty ();
  checkTerminalSize ();
  loadFont (argc > 1 ? argv[1] : "font.bin");
  rk_init ();

  init_screen ();

  for (int i = 0; i < MEMORY_SIZE; i++)
    sc_memorySet (i, (int)(rand () % 32768));

  printMemory ();
  printAccumulator ();
  printFlags ();
  printCommand ();
  printCounters ();
  updateTerm ();

  setSelectedCell (0);

  int notShouldExit = 1;
  while (notShouldExit)
    {
      mt_gotoXY (0, COMMAND_LINE_Y);
      Keys key = K_0;
      rk_readkey (&key);

      switch (key)
        {

        case K_s:
          im_memorySave ();
          break;

        case K_l:
          im_memoryLoad ();
          break;

        case K_i:
          im_reset ();
          break;

        case K_esc:
          im_exit (&notShouldExit);
          break;

        case K_left:
          im_memoryLeft ();
          break;

        case K_right:
          im_memoryRight ();
          break;

        case K_up:
          im_memoryUp ();
          break;

        case K_down:
          im_memoryDown ();
          break;

        case K_enter:
          im_memoryWrite ();
          break;

        case K_F5:
          im_accumulator ();
          break;

        case K_F6:
          im_incounter ();

        default:
          continue;
        }
    }
  mt_gotoXY (0, COMMAND_LINE_Y);

  bc_freeSpace ();

  return 0;
}