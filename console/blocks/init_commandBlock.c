#include <console/console.h>

void
init_commandBlock ()
{
  mt_gotoXY (FLAGS_OFFSET_X, INCOUNTER_OFFSET_Y);

  write (1, "┌──────", 22);
  mt_setfgcolor (RED);
  write (1, " Команда ", 17);
  mt_setdefaultcolor ();
  write (1, "──────┐", 22);

  mt_gotoXY (FLAGS_OFFSET_X, INCOUNTER_OFFSET_Y + 1);
  write (1, "│ ", 5);
  mt_gotoXY (FLAGS_OFFSET_X + MINI_BLOCK_WIDTH - 2, INCOUNTER_OFFSET_Y + 1);
  write (1, " │", 5);

  mt_gotoXY (FLAGS_OFFSET_X, INCOUNTER_OFFSET_Y + 2);
  write (1, "└─────────────────────┘\n", 71);
}