#include <console/console.h>

void
init_termBlock ()
{
  mt_gotoXY (TERM_OFFSET_X, LOW_OFFSET_Y);

  write (1, "┌", 4);
  mt_setfgcolor (GREEN);
  mt_setbgcolor (WHITE);
  write (1, " IN--OUT ", 10);
  mt_setdefaultcolor ();
  write (1, "┐", 4);

  for (int i = LOW_OFFSET_Y + 1; i < LOW_OFFSET_Y + 6; i++)
    {
      mt_gotoXY (TERM_OFFSET_X, i);
      write (1, "│", 4);
      mt_gotoXY (KEYBINDS_OFFSET_X - 1, i);
      write (1, "│", 4);
    }
  mt_gotoXY (TERM_OFFSET_X, LOW_OFFSET_Y + 6);
  write (1, "└─────────┘\n", 35);
}