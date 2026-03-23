#include <mySimpleComputer/sc_variables.h>

int
sc_incounterSet (int value)
{
  if (checkCellOverflow (value))
    return -1;

  if (value == NEGATIVE_ZERO)
    return -2;

  incounter = value;
  return 0;
}