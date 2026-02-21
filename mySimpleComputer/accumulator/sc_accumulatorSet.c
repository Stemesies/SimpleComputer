#include "../sc_variables.h"

int
sc_accumulatorSet (int value)
{

  int validatorResult = sc_commandValidate (value);
  if (validatorResult != 0)
    return validatorResult;

  setAccumulator (value);
  return 0;
}