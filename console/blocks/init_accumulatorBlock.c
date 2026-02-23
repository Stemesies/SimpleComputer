#include <console/console.h>

void
init_accumulatorBlock ()
{
  mt_gotoXY (ACCUMULATOR_OFFSET_X, 0);

  write (1, "┌────", 16);
  mt_setfgcolor (RED);
  write (1, " Аккумулятор ", 25);
  mt_setdefaultcolor ();
  write (1, "────┐", 16);

  mt_gotoXY (ACCUMULATOR_OFFSET_X, 2);
  write (1, "│ ", 5);
  mt_gotoXY (ACCUMULATOR_OFFSET_X + MINI_BLOCK_WIDTH - 2, 2);
  write (1, " │", 5);

  mt_gotoXY (ACCUMULATOR_OFFSET_X, 3);
  write (1, "└─────────────────────┘\n", 71);
}