#include <mySimpleComputer/sc_variables.h>

int
sc_memoryGet (int address, int *value)
{

  if (value == NULL)
    return -1;

  if (checkAddressOverflow (address))
    return -1;

  *value = memory[address];
  return 0;
}