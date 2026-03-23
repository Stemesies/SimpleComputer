#include <console/console.h>
#include <include/utils.h>

static int history[5][2]
    = { { -1, -1 }, { -1, -1 }, { -1, -1 }, { -1, -1 }, { -1, -1 } };
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

      if (address == -1)
        continue;

      writef ("%02x%c ", address, input == 1 ? '<' : '>');

      printCellValue (value, NOTHING, NOTHING);
    }
}

int *
printTerm (int address, int input)
{

  if (input < 0 || input > 1)
    return NULL;

  int value = 0;
  sc_memoryGet (address, &value);

  history[head][0] = address;
  history[head][1] = ((value << 1) | input);
  int *pointer = history[head] + 1;
  head++;

  if (head >= 5)
    head = 0;

  updateTerm ();
  return pointer;
}