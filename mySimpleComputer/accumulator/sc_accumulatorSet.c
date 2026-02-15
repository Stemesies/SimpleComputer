#include "../sc_variables.h"

int
sc_accumulatorSet (int value)
{

  if (value < 0 || value > MAX_CELL_VALUE)
    return -1;

  setAccumulator (value);
  return 0;
}