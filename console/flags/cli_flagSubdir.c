#include <console/console.h>

void
cli_flagSubdir ()
{
  char action = ' ';

  printInputPointer ("[flag managment] ");
  mScanf ("%c", &action, return);

  switch (action)
    {

    case 's':
      cli_setFlag ();
      break;

    case 'r':
      sc_regInit ();
      printf ("Successful register reset.\n");
      break;

    default:
      printf ("Invalid subcommand.\n");
      break;
    }
}