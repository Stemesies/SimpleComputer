#include <console/console.h>

void
cli_setAccumulator ()
{
  int addr = 0;
  int value = 0;

  printInputPointer ("[accumulator] select cell to copy value from");
  mScanf ("%d", &addr, return);

  if (sc_memoryGet (addr, &value) != 0)
    {
      printf ("Invalid address: %d.\n", addr);
      return;
    }

  if (sc_accumulatorSet (value) == -1)
    printf ("Invalid value. Acceptable: [0x0;0x%x]\n", MAX_CELL_VALUE);
}