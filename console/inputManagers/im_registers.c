#include <console/console.h>
#include <include/myReadKey.h>
#include <include/myTerm.h>

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
      return;
    }

  mt_gotoXY (RAM_WIDTH + 3 + 4, 2);
  printCellValue (value, BLACK, RED);

  mt_gotoXY (0, COMMAND_LINE_Y);
  mt_delline ();

  if (result == 1)
    {
      mt_setdefaultcolor ();
      printAccumulator ();
      return;
    }
  invalidCellExplain (result);
}

void
im_accumulator ()
{

  int notShouldExit = 1;

  hideSelectedCell ();
  init_drawAccumulatorBox (BLACK, RED);
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

  init_drawAccumulatorBox (RED, NOTHING);
  printAccumulator ();
  printSelectedCell ();

  mt_gotoXY (0, COMMAND_LINE_Y);
  mt_delline ();
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
      incounterCell = value;
      moveIncounterCell ();
      printCounters ();
      mt_gotoXY (RAM_WIDTH + 3 + 14, INCOUNTER_OFFSET_Y + 1);
      printCellValue (value, BLACK, GREEN);
      printCommand ();

      return;
    }

  mt_gotoXY (RAM_WIDTH + 3 + 14, INCOUNTER_OFFSET_Y + 1);
  printCellValue (value, BLACK, RED);

  mt_gotoXY (0, COMMAND_LINE_Y);
  mt_delline ();

  if (result == 1)
    {
      mt_setdefaultcolor ();
      printCounters ();
      return;
    }

  invalidCellExplain (result);
}

void
im_incounter ()
{

  int notShouldExit = 1;

  hideSelectedCell ();
  init_drawIncounterBox (BLACK, RED);
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

  init_drawIncounterBox (RED, NOTHING);
  printCounters ();
  printSelectedCell ();

  mt_gotoXY (0, COMMAND_LINE_Y);
  mt_delline ();
}