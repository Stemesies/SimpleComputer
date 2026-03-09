#include <console/console.h>

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

  while (printedI < 5)
    {
      mt_gotoXY (TERM_OFFSET_X + 1, LOW_OFFSET_Y + 1 + printedI);
      if (history[i][0] != -1)
        {
          sprintf (render, "%02x%c ", history[i][0],
                   history[i][1] == -1 ? '<' : '>');
          write (1, render, 7);
          if (history[i][1] != -1)
            printCellValue (history[i][1], NOTHING, NOTHING);
          else
            write (1, "     ", 6);
        }

      i++;
      printedI++;

      if (i >= 5)
        i = 0;
    }
}

void
printTerm (int address, int input)
{
  int value = 0;

  if (input != 0 || address == -1)
    value = -1;
  else
    sc_memoryGet (address, &value);

  history[head][0] = address;
  history[head][1] = value;
  head++;

  if (head >= 5)
    head = 0;

  updateTerm ();
}