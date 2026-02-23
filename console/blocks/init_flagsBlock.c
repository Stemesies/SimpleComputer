#include <console/console.h>

void
init_flagsBlock ()
{
  mt_gotoXY (FLAGS_OFFSET_X, 0);

  write (1, "┌──", 10);
  mt_setfgcolor (RED);
  write (1, " Регистр  флагов ", 31);
  mt_setdefaultcolor ();
  write (1, "──┐", 10);

  mt_gotoXY (FLAGS_OFFSET_X, 2);
  write (1, "│   ", 7);
  mt_gotoXY (FLAGS_OFFSET_X + MINI_BLOCK_WIDTH - 2, 2);
  write (1, " │", 5);

  mt_gotoXY (FLAGS_OFFSET_X, 3);
  write (1, "└─────────────────────┘\n", 71);
}