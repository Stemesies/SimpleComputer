#include <mySimpleComputer/sc_variables.h>

int
sc_accumulatorSet (int value)
{
  if (checkCellOverflow (value))
    return -1;

  if (value == NEGATIVE_ZERO)
    return -2;

  accumulator = value;
  return 0;
}