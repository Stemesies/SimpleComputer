#include "../sc_variables.h"

int
sc_memoryGet (int address, int *value)
{

  if (address < 0 || address > MEMORY_SIZE)
    return -1;

  if (value == 0 /* Null */)
    return -1;

  *value = getMemory ()[address];
  return 0;
}