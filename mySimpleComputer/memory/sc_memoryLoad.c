#include "../sc_variables.h"
#include <stdio.h>

int
sc_memoryLoad (char *filename)
{
  if (filename == NULL)
    return -1;

  FILE *file = fopen (filename, "r");

  if (file == NULL)
    return -1;

  int buffer[MEMORY_SIZE];

  size_t count = fread (buffer, sizeof (int), MEMORY_SIZE, file);

  fclose (file);

  if (count < MEMORY_SIZE)
    return -1;

  int *memory = getMemory ();
  for (int i = 0; i < MEMORY_SIZE; i++)
    {
      memory[i] = buffer[i];
    }

  return 0;
}