#include "../sc_variables.h"

int
sc_incounterSet (int value)
{

  int validatorResult = sc_commandValidate (value);
  if (validatorResult != 0)
    return validatorResult;

  setIncounter (value);
  return 0;
}