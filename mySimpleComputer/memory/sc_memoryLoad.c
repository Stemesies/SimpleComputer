#include <mySimpleComputer/sc_variables.h>
#include <stdio.h>

int
sc_memoryLoad (char *filename)
{
  if (filename == NULL)
    return -1;

  FILE *file = fopen (filename, "r");

  if (file == NULL)
    return -2;

  int buffer[MEMORY_SIZE];

  size_t count = fread (buffer, sizeof (int), MEMORY_SIZE, file);

  fclose (file);

  if (count < MEMORY_SIZE)
    return -3;

  for (int i = 0; i < MEMORY_SIZE; i++)
    memory[i] = buffer[i];

  sc_notifyListener (STATE_MEMORY_UPDATE, 0);
  sc_notifyListener (STATE_INCOUNTER_UPDATE, 0);

  return 0;
}