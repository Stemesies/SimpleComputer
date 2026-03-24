#include "sc_variables.h"

void
sc_reset ()
{
  tickCounter = 0;
  commandStage = 0;

  sc_memoryInit ();
  sc_regInit ();
  sc_accumulatorInit ();
  sc_incounterInit ();
  sc_notifyListener (STATE_RESET, 0);
}