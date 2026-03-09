#include "../sc_variables.h"

int
sc_memoryInit ()
{
  int *memory = getMemory ();
  for (int i = 0; i < MEMORY_SIZE; i++)
    {
      memory[i] = 0;
    }
  return 0;
}