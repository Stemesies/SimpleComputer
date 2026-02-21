#include "../sc_variables.h"

int
sc_incounterGet (int *value)
{

  if (value == 0 /* Null */)
    return -1;

  *value = getIncounter ();

  return 0;
}