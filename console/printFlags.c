#include <console/console.h>

#define printOrUnderline(chara, checkedRegister)                              \
  if ((registers & checkedRegister) == checkedRegister)                       \
    putchar (chara);                                                          \
  else                                                                        \
    putchar ('_');

void
printFlags ()
{
  int registers;

  if (sc_regGet (REG_ALL, &registers) != 0)
    {
      printf ("Something went very wrong.\n");
      return;
    }

  printOrUnderline ('P', REG_OVERFLOW);
  putchar (' ');
  printOrUnderline ('0', REG_ZERO_DIV);
  putchar (' ');
  printOrUnderline ('M', REG_OUT_OF_BOUNDS);
  putchar (' ');
  printOrUnderline ('T', REG_TICK_IGNORE);
  putchar (' ');
  printOrUnderline ('E', REG_INVALID_COMMAND);
}