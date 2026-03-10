#include "include/mySimpleComputer.h"
#include <console/console.h>
#include <unistd.h>

static int history[5][2]
    = { { -1, -1 }, { -1, -1 }, { -1, -1 }, { -1, -1 }, { -1, -1 } };
static char render[9] = { 0 };
static unsigned char head = 0;
static unsigned char printedI = 0;
static unsigned char i = 0;

void
updateTerm ()
{
  printedI = 0;
  i = head;

  int address = 0;
  int value = 0;
  int input = 0;

  while (printedI < 5)
    {
      mt_gotoXY (TERM_OFFSET_X + 1, LOW_OFFSET_Y + 1 + printedI);
      address = history[i][0];
      value = (history[i][1] >> 1);
      input = history[i][1] & 1;

      i++;
      printedI++;
      if (i >= 5)
        i = 0;

      switch (address)
        {
        case -1:
          continue;
        case -2:
          sprintf (render, "ac%c ", input == 1 ? '<' : '>');
          break;
        case -3:
          sprintf (render, "ic%c ", input == 1 ? '<' : '>');
          break;
        default:
          sprintf (render, "%02x%c ", address, input == 1 ? '<' : '>');
          break;
        }

      write (1, render, 7);
      printCellValue (value, NOTHING, NOTHING);
    }
}

void
printTerm (int address, int input)
{

  if (input < 0 || input > 1)
    return;

  int value = 0;
  switch (address)
    {
    case -2:
      sc_accumulatorGet (&value);
      break;
    case -3:
      sc_incounterGet (&value);
      break;
    default:
      sc_memoryGet (address, &value);
      break;
    }

  history[head][0] = address;
  history[head][1] = ((value << 1) | input);
  head++;

  if (head >= 5)
    head = 0;

  updateTerm ();
}