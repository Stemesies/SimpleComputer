#include <mySimpleComputer/sc_variables.h>

int
sc_incounterGet (int *value)
{

  if (value == NULL)
    return -1;

  *value = incounter;

  return 0;
}