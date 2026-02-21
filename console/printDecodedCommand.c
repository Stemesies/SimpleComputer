#include <console/console.h>

#define TOTAL (BITS_PER_OPERAND + BITS_PER_COMMAND + 1)

void
printBin (int value, int lengthInBits)
{
  for (int i = 0; i < lengthInBits; i++)
    {
      if ((value >> (lengthInBits - i - 1)) & 0x1)
        putchar ('1');
      else
        putchar ('0');
    }
}

void
printDecodedCommand (int value)
{
  printf ("Hex: 0x%x;\nDec: %d;\nOct: %o;\nBin: ", value, value, value);
  printBin (value, TOTAL);
  putchar ('\n');
}