#include <console/console.h>

#define TOTAL (BITS_PER_OPERAND + BITS_PER_COMMAND + 1)

void
printBin (int value)
{
  for (int i = 0; i < TOTAL; i++)
    {
      if ((value >> (TOTAL - i - 1)) & 0x1)
        putchar ('1');
      else
        putchar ('0');
    }
}

void
cli_breakdownCommand (int encodedCommand)
{
  printf ("Hex: 0x%x;\nDec: %d;\nOct: %o;\nBin: ", encodedCommand,
          encodedCommand, encodedCommand);
  printBin (encodedCommand);
  putchar ('\n');
}