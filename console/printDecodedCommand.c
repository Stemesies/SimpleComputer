#include <console/console.h>

#define TOTAL (BITS_PER_OPERAND + BITS_PER_COMMAND + 1)

void
printBin (int value, int lengthInBits)
{
  for (int i = 0; i < lengthInBits; i++)
    {
      if ((value >> (lengthInBits - i - 1)) & 0x1)
        write (1, "1", 1);
      else
        write (1, "0", 1);
    }
}

void
printDecodedCommand (int value)
{
  mt_gotoXY (2, DETAILED_CELL_OFFSET_Y + 1);
  char render[45] = { 0 };
  sprintf (render, "dec: %05d | oct: %05o | hex: %04x    bin: ", value, value,
           value);

  write (1, render, 45);
  printBin (value, TOTAL);
  putchar ('\n');
}