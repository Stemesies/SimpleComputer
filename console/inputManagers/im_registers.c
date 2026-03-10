#include "include/mySimpleComputer.h"
#include <console/console.h>
#include <include/myReadKey.h>
#include <include/myTerm.h>
#include <unistd.h>

void
im_writeAccumulator ()
{
  int initialAccumulatorValue = 0;
  sc_accumulatorGet (&initialAccumulatorValue);

  int value = 0;
  mt_gotoXY (RAM_WIDTH + 3 + 4, 2);
  printCellValue (initialAccumulatorValue, GREEN, GREEN);
  mt_gotoXY (RAM_WIDTH + 3 + 4, 2);

  mt_setbgcolor (BLACK);
  int result = rk_readvalue (&value, 0);
  mt_setdefaultcolor ();

  if (result == 0)
    {
      sc_accumulatorSet (value);
      printAccumulator ();
      mt_gotoXY (RAM_WIDTH + 3 + 4, 2);
      printCellValue (value, BLACK, GREEN);
      printTerm (-2, 1);
      return;
    }

  mt_gotoXY (RAM_WIDTH + 3 + 4, 2);
  printCellValue (value, BLACK, RED);

  mt_gotoXY (0, COMMAND_LINE_Y);
  mt_delline ();
  mt_setfgcolor (RED);
  switch (result)
    {
    case 1:
      mt_setdefaultcolor ();
      printAccumulator ();
      break;

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
    case -11:
      write (1, "Command validator: command out of bounds.", 42);
      break;
    default:
      write (1, "Unknown error", 14);
    }
  mt_setdefaultcolor ();
}

void
im_accumulator ()
{

  int notShouldExit = 1;

  printCell (getSelectedCell (), RESET, NOTHING);
  bc_box (ACCUMULATOR_OFFSET_X, 0, ACCUMULATOR_OFFSET_X + MINI_BLOCK_WIDTH, 3,
          NOTHING, NOTHING, " Аккумулятор ", BLACK, RED);
  printAccumulator ();

  while (notShouldExit)
    {

      mt_gotoXY (0, COMMAND_LINE_Y);
      Keys key = K_0;
      rk_readkey (&key);

      switch (key)
        {

        case K_esc:
          notShouldExit = 0;
          break;

        case K_enter:
          im_writeAccumulator ();
          break;

        default:
          continue;
        }
    }

  bc_box (ACCUMULATOR_OFFSET_X, 0, ACCUMULATOR_OFFSET_X + MINI_BLOCK_WIDTH, 3,
          NOTHING, NOTHING, " Аккумулятор ", RED, NOTHING);
  printAccumulator ();
  printCell (getSelectedCell (), BLACK, WHITE);
}

void
im_writeIncounter ()
{
  int initialIncounterValue = 0;
  sc_incounterGet (&initialIncounterValue);

  int value = 0;
  mt_gotoXY (RAM_WIDTH + 3 + 14, INCOUNTER_OFFSET_Y + 1);
  printCellValue (initialIncounterValue, GREEN, GREEN);
  mt_gotoXY (RAM_WIDTH + 3 + 14, INCOUNTER_OFFSET_Y + 1);

  mt_setbgcolor (BLACK);
  int result = rk_readvalue (&value, 0);
  mt_setdefaultcolor ();

  if (result == 0)
    {
      sc_incounterSet (value);
      printCounters ();
      mt_gotoXY (RAM_WIDTH + 3 + 14, INCOUNTER_OFFSET_Y + 1);
      printCellValue (value, BLACK, GREEN);
      printTerm (-3, 1);
      printCommand ();
      return;
    }

  mt_gotoXY (RAM_WIDTH + 3 + 14, INCOUNTER_OFFSET_Y + 1);
  printCellValue (value, BLACK, RED);

  mt_gotoXY (0, COMMAND_LINE_Y);
  mt_delline ();
  mt_setfgcolor (RED);
  switch (result)
    {
    case 1:
      mt_setdefaultcolor ();
      printCounters ();
      break;

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
    case -11:
      write (1, "Command validator: command out of bounds.", 42);
      break;
    default:
      write (1, "Unknown error", 14);
    }
  mt_setdefaultcolor ();
}

void
im_incounter ()
{

  int notShouldExit = 1;

  printCell (getSelectedCell (), RESET, NOTHING);
  bc_box (ACCUMULATOR_OFFSET_X, INCOUNTER_OFFSET_Y,
          ACCUMULATOR_OFFSET_X + MINI_BLOCK_WIDTH, INCOUNTER_OFFSET_Y + 3,
          NOTHING, NOTHING, " Счетчик  команд ", BLACK, RED);
  printCounters ();

  while (notShouldExit)
    {

      mt_gotoXY (0, COMMAND_LINE_Y);
      Keys key = K_0;
      rk_readkey (&key);

      switch (key)
        {

        case K_esc:
          notShouldExit = 0;
          break;

        case K_enter:
          im_writeIncounter ();
          break;

        default:
          continue;
        }
    }

  bc_box (ACCUMULATOR_OFFSET_X, INCOUNTER_OFFSET_Y,
          ACCUMULATOR_OFFSET_X + MINI_BLOCK_WIDTH, INCOUNTER_OFFSET_Y + 3,
          NOTHING, NOTHING, " Счетчик  команд ", RED, NOTHING);
  printCounters ();
  printCell (getSelectedCell (), BLACK, WHITE);
}