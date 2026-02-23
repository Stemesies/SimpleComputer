#include <console/console.h>
#include <include/myTerm.h>

void
printMemory ()
{
  for (int i = 0; i < MEMORY_SIZE; i++)
    {
      printCell (i, DEFAULT, DEFAULT);
    }
  putchar ('\n');
}