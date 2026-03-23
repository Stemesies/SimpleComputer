#include <mySimpleComputer/sc_variables.h>

int
sc_memorySet (int address, int value)
{

  if (checkAddressOverflow (address))
    return -1;

  if (value == NEGATIVE_ZERO)
    return -2;

  memory[address] = value;
  return 0;
}