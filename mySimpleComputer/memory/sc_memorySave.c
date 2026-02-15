#include "../sc_variables.h"
#include <stdio.h>

int
sc_memorySave (char *filename)
{
  if (filename == NULL)
    return -1;

  FILE *file = fopen (filename, "w");

  if (file == NULL)
    return -1;

  size_t count = fwrite (getMemory (), sizeof (int), MEMORY_SIZE, file);

  fclose (file);

  if (count < MEMORY_SIZE)
    return -1;

  return 0;
}