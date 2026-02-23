#include <console/console.h>

#define printOrUnderline(chara, checkedRegister)                              \
  if ((registers & checkedRegister) == checkedRegister)                       \
    write (1, chara, 1);                                                      \
  else                                                                        \
    write (1, "_", 1);

void
printFlags ()
{

  int registers;

  if (sc_regGet (REG_ALL, &registers) != 0)
    {
      printf ("Something went very wrong.\n");
      return;
    }

  mt_gotoXY (FLAGS_OFFSET_X + 5, 2);
  printOrUnderline ("P", REG_OVERFLOW);
  write (1, "  ", 2);
  printOrUnderline ("0", REG_ZERO_DIV);
  write (1, "  ", 2);
  printOrUnderline ("M", REG_OUT_OF_BOUNDS);
  write (1, "  ", 2);
  printOrUnderline ("T", REG_TICK_IGNORE);
  write (1, "  ", 2);
  printOrUnderline ("E", REG_INVALID_COMMAND);
}