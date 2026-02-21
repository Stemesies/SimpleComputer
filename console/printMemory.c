#include <console/console.h>

void
printMemory ()
{
  for (int i = 0; i < MEMORY_SIZE; i++)
    {
      if (i != 0 && i % 10 == 0)
        putchar ('\n');

      printCell (i);
      putchar (' ');
    }
  putchar ('\n');
}