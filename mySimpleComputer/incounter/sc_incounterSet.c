#include "../sc_variables.h"

int
sc_incounterSet (int value)
{

  if (value < 0 || value > MAX_CELL_VALUE)
    return -1;

  setIncounter (value);
  return 0;
}