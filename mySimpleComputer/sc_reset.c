#include "mySimpleComputer/sc_variables.h"
#include <include/mySimpleComputer.h>

void
sc_reset ()
{
  sc_memoryInit ();
  sc_regInit ();
  sc_accumulatorInit ();
  sc_incounterInit ();
  resetTickCounter ();
  sc_notifyListener (STATE_RESET, 0);
  sc_notifyListener (STATE_INCOUNTER_UPDATE, 0);
  sc_notifyListener (STATE_FLAG_UPDATE, 0);
  sc_notifyListener (STATE_ACCUMULATOR_UPDATE, 0);
  sc_notifyListener (STATE_MEMORY_UPDATE, 0);
}