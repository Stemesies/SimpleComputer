#include <console/console.h>

void
cli_printMemory ()
{
  for (int i = 0; i < MEMORY_SIZE; i++)
    {
      if (i != 0 && i % 10 == 0)
        putchar ('\n');

      cli_printCell (i);
      putchar (' ');
    }
  putchar ('\n');
}