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
systemListener (int key, int options)
{
  static int tickLast = 0;
  static int incLast = 0;
  static int incThis = 0;

  switch (key)
    {
    case STATE_ACCUMULATOR_UPDATE:
      printAccumulator ();
      break;
    case STATE_INCOUNTER_UPDATE:
      sc_incounterGet (&incThis);
      if (incLast != incThis)
        {
          incLast = incThis;
          tickLast = sc_tickCounter ();
        }
      mt_gotoXY (3, LOW_OFFSET_Y + 2);
      char buffer[40] = "";
      sprintf (buffer, "TickCounter: %d      ", sc_tickCounter ());
      write (1, buffer, strlen (buffer));
      mt_gotoXY (3, LOW_OFFSET_Y + 3);
      sprintf (buffer, "Current instruction ticks: %d     ",
               sc_tickCounter () - tickLast);
      write (1, buffer, strlen (buffer));

      mt_gotoXY (3, LOW_OFFSET_Y + 4);
      write (1, "Current command: ", 18);
      p_determineCommand ();
      sprintf (buffer, " Idle: %d      ", options);
      write (1, buffer, strlen (buffer));

      printCounters ();
      sc_incounterGet (&incounterCell);
      incounterCellIsIdling = options;

      moveIncounterCell ();

      break;

    case STATE_FLAG_UPDATE:
      printFlags ();
      break;
    case STATE_CELL_UPDATE:
      printCell (options, NOTHING, NOTHING);

      if (options == selectedCell)
        printSelectedCell ();
      else if (options == incounterCell)
        printIncounterCell ();

      break;

    case STATE_CPUINFO:
      mt_gotoXY (0, COMMAND_LINE_Y);
      write (1, "2 гига 2 ядра", 22);
      break;

    case STATE_RESET:
      printMemory ();
      printAccumulator ();
      printCounters ();
      printCommand ();
      printSelectedCell ();
      mt_gotoXY (0, COMMAND_LINE_Y);
      mt_delline ();
      break;

    case STATE_READ_REQUEST:;
      int *termField = printTerm (options, 1);
      int value = 0;
      int result = 1;

      while (result != 0)
        {
          mt_gotoXY (TERM_OFFSET_X + 5, LOW_OFFSET_Y + 5);
          result = rk_readvalue (&value, 0);
          *termField = ((value << 1) | 1);
          mt_gotoXY (0, COMMAND_LINE_Y);
          mt_delline ();
          mt_setfgcolor (RED);
          switch (result)
            {
            case 0:
              mt_setdefaultcolor ();
              sc_memorySet (options, value);
              sc_regSet (REG_TICK_IGNORE, 0);
              printFlags ();
              systemListener (STATE_CELL_UPDATE, options);
              break;
            case 1:
              mt_setdefaultcolor ();
              mt_gotoXY (TERM_OFFSET_X + 5, LOW_OFFSET_Y + 5);
              write (1, "cncld", 6);
              mt_gotoXY (0, COMMAND_LINE_Y);
              return -1;

            case -20:
              write (1, "Illegal cell format and/or illegal symbols.", 44);
              break;
            case -10:
              write (1, "Illegal sign. Allowed only '+' or '-'.", 39);
              break;
            case -2:
              write (1, "Command field overflow.", 24);
              break;
            case -3:
              write (1, "Operand field overflow.", 24);
              break;
            default:
              write (1, "Unknown error", 14);
            }
          mt_setdefaultcolor ();
        }
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

  // for (int i = 0; i < MEMORY_SIZE; i++)
  //   sc_memorySet (i, (int)(rand () % 32768));

  printMemory ();
  printAccumulator ();
  printFlags ();
  printCommand ();
  printCounters ();
  updateTerm ();

  moveSelectedCell (0);
  sc_setStateListener (systemListener);
  IG_init ();

  int notShouldExit = 1;
  Keys key = K_0;

  while (notShouldExit)
    {
      mt_gotoXY (0, COMMAND_LINE_Y);
      rk_readkey (&key);

      int isIdle;
      sc_regGet (REG_TICK_IGNORE, &isIdle);

      switch (key)
        {

        case K_s:
          if (isIdle != 0)
            im_memorySave ();
          break;

        case K_l:
          if (isIdle != 0)
            im_memoryLoad ();
          break;

        case K_i:
          im_reset ();
          break;

        case K_r:
          sc_regSet (REG_TICK_IGNORE, 0);
          printFlags ();
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

          if (isIdle != 0)
            im_memoryWrite ();
          break;

        case K_F5:
          if (isIdle != 0)
            im_accumulator ();
          break;

        case K_F6:
          if (isIdle != 0)
            im_incounter ();

        default:
          continue;
        }
    }
  mt_gotoXY (0, COMMAND_LINE_Y);

  bc_freeSpace ();

  return 0;
}