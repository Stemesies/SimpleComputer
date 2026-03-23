#include "include/mySimpleComputer.h"
#include "include/myTerm.h"
#include <console/console.h>
#include <include/myReadKey.h>
#include <stdlib.h>
#include <unistd.h>

int selectedCell = 0;
int incounterCell = 0;
int incounterCellIsIdling = 0;

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

int
systemListener (int key, int options)
{
  switch (key)
    {
    case STATE_ACCUMULATOR_UPDATE:
      printAccumulator ();
      break;
    case STATE_INCOUNTER_UPDATE:
      l_incounterUpdate (options);
      break;
    case STATE_FLAG_UPDATE:
      printFlags ();
      break;
    case STATE_CELL_UPDATE:
      l_cellUpdate (options);
      break;
    case STATE_CPUINFO:
      mt_gotoXY (0, COMMAND_LINE_Y);
      write (1, "2 гига 2 ядра", 22);
      break;
    case STATE_RESET:
      l_reset ();
      mt_gotoXY (0, COMMAND_LINE_Y);
      break;
    case STATE_READ_REQUEST:;
      if (l_readRequest (options) != 0)
        return -1;
      break;
    case STATE_WRITE_REQUEST:
      printTerm (options, 0);
      break;
    }

  mt_gotoXY (0, COMMAND_LINE_Y);
  return 0;
}

int
main (int argc, char *argv[])
{
  checkTty ();
  checkTerminalSize ();
  loadFont (argc > 1 ? argv[1] : "font.bin");
  rk_init ();

  init_screen ();

  l_reset ();

  moveSelectedCell (0);
  sc_setStateListener (systemListener);
  IG_init ();

  int notShouldExit = 1;
  Keys key = K_0;
  int isRunningVar;

  while (notShouldExit)
    {

      mt_gotoXY (0, COMMAND_LINE_Y);
      rk_readkey (&key);

      isRunningVar = sc_isRunning ();

      switch (key)
        {

        case K_s:
          if (isRunningVar == 0)
            im_memorySave ();
          break;

        case K_l:
          if (isRunningVar == 0)
            im_memoryLoad ();
          break;

        case K_t:
          if (isRunningVar == 0)
            ICR_tick ();
          break;

        case K_i:
          if (isRunningVar == 0)
            im_reset ();
          break;

        case K_r:
          if (isRunningVar == 0)
            sc_regSet (REG_TICK_IGNORE, 0);
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
          if (isRunningVar == 0)
            im_editCell ();
          break;

        case K_F5:
          if (isRunningVar == 0)
            im_accumulator ();
          break;

        case K_F6:
          if (isRunningVar == 0)
            im_incounter ();

        default:
          continue;
        }
    }

  mt_gotoXY (0, COMMAND_LINE_Y);
  bc_freeSpace ();

  return 0;
}