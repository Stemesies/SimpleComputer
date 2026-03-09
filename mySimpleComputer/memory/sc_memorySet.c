#include "../sc_variables.h"

int
sc_memorySet (int address, int value)
{

  if (address < 0 || address > MEMORY_SIZE)
    return -1;

  if (value == 0 /* Null */)
    return -4;

  // int validatorResult = sc_commandValidate (value);
  // if (validatorResult != 0)
  //   return validatorResult;

  getMemory ()[address] = value;
  return 0;
}