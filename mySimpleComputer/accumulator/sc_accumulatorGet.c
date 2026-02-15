#include "../sc_variables.h"

int
sc_accumulatorGet (int *value)
{

  if (value == 0 /* Null */)
    return -1;

  *value = getAccumulator ();

  return 0;
}