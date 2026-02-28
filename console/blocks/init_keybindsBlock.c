#include <console/console.h>

void
init_keybindsBlock ()
{
  mt_gotoXY (KEYBINDS_OFFSET_X, LOW_OFFSET_Y);

  write (1, "┌──────────", 34);
  mt_setfgcolor (GREEN);
  mt_setbgcolor (WHITE);
  write (1, " Клавиши ", 17);
  mt_setdefaultcolor ();
  write (1, "───────────┐", 37);

  mt_gotoXY (KEYBINDS_OFFSET_X, LOW_OFFSET_Y + 1);
  write (1, "│l - load  s - save  i - reset │", 37);
  mt_gotoXY (KEYBINDS_OFFSET_X, LOW_OFFSET_Y + 2);
  write (1, "│r - run  t - step             │", 37);
  mt_gotoXY (KEYBINDS_OFFSET_X, LOW_OFFSET_Y + 3);
  write (1, "│ESC - выход                   │", 42);
  mt_gotoXY (KEYBINDS_OFFSET_X, LOW_OFFSET_Y + 4);
  write (1, "│F5 - accumulator              │", 37);
  mt_gotoXY (KEYBINDS_OFFSET_X, LOW_OFFSET_Y + 5);
  write (1, "│F6 - instruction counter      │", 37);
  mt_gotoXY (KEYBINDS_OFFSET_X, LOW_OFFSET_Y + 6);
  write (1, "└──────────────────────────────┘", 97);
}