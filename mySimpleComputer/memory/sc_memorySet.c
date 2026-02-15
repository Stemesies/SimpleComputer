#include "../sc_variables.h"

int
sc_memorySet (int address, int value)
{

  if (address < 0 || address > MEMORY_SIZE)
    return -1;

  if (value < 0 || value > MAX_CELL_VALUE)
    return -2;

  if (value == 0 /* Null */)
    return -3;

  getMemory ()[address] = value;
  return 0;
}