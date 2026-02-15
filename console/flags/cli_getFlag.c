#include <console/console.h>

/*
Возвращает маску выбранного регистра.
*/
int
cli_getFlag ()
{
  char address = ' ';

  printInputPointer ("[flag managment] select register");
  mScanf ("%c", &address, return -1);

  switch (address)
    {

    case 'P':
      return REG_OVERFLOW;
    case '0':
      return REG_ZERO_DIV;
    case 'M':
      return REG_OUT_OF_BOUNDS;
    case 'T':
      return REG_TICK_IGNORE;
    case 'E':
      return REG_INVALID_COMMAND;
    default:
      printf ("Invalid register. Available: [P, 0, M, T, E]\n");
      return -1;
    }
}