#include <console/console.h>

static int accum = 0, incoun = 0, lastCellAddr = 0;

void
cli_setLastCell (int addr)
{
  lastCellAddr = addr;
}

void
cli_printMachineStatus ()
{
  sc_accumulatorGet (&accum);
  sc_incounterGet (&incoun);

  cli_printFlags ();
  printf (" [accumulator: (0x%x) ", accum);
  cli_printDecodedCommand (accum);
  printf (", incounter: (0x%x) ", incoun);
  cli_printDecodedCommand (incoun);
  printf (", lastCell: (%d) ", lastCellAddr);
  cli_printCell (lastCellAddr);

  printf ("]\n");
}