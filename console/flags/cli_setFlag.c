#include <console/console.h>

void
cli_setFlag ()
{
  int flag = cli_getFlag ();
  int value = 0;

  if (flag == -1)
    return;

  printInputPointer ("[flag managment] enter value: ");
  mScanf ("%d", &value, return);

  if (value != 0 && value != 1)
    {
      printf ("Illegal value: %d. Available: [0;1]\n", value);
      return;
    }

  switch (sc_regSet (flag, value == 1 ? flag : 0))
    {
    case 0:
      printf ("Register's value for 0x%x updated to %d\n", flag, value);
      break;
    case -1:
      printf ("Flag not found.\n");
      break;
    case -2:
      printf ("Trying to modify wrong flag.\n");
      break;
    }
}