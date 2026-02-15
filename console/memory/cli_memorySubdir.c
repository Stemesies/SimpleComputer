#include <console/console.h>

void
cli_memorySubdir ()
{
  char action = ' ';
  int address = 0;

  printInputPointer ("[memory managment] ");
  mScanf ("%c", &action, return);

  switch (action)
    {
    case 'p':
      cli_printMemory ();
      putchar ('\n');
      break;
    case 's':
      cli_setMemoryCell ();
      break;
    case 'c':
      printInputPointer ("[memory managment] select cell");
      mScanf ("%d", &address, return);
      cli_printCell (address);
      putchar ('\n');
      cli_setLastCell (address);
      break;
    case 'b':
      printInputPointer ("[memory managment] select cell");
      mScanf ("%d", &address, return);
      cli_breakDownCell (address);
      cli_setLastCell (address);
      break;
    case 'r':
      sc_memoryInit ();
      printf ("Successful memory reset.\n");
      break;

    default:
      printf ("Invalid subcommand.\n");
      break;
    }
}