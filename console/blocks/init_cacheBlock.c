#include <console/console.h>

void
init_cacheBlock ()
{
  mt_gotoXY (0, LOW_OFFSET_Y);

  write (1, "┌───────────────────────", 73);
  mt_setfgcolor (GREEN);
  mt_setbgcolor (WHITE);
  write (1, " Кеш процессора ", 30);
  mt_setdefaultcolor ();
  write (1, "────────────────────────┐", 76);

  for (int i = LOW_OFFSET_Y + 1; i < LOW_OFFSET_Y + 6; i++)
    {
      mt_gotoXY (0, i);
      write (1, "│", 4);
      mt_gotoXY (TERM_OFFSET_X - 1, i);
      write (1, "│", 4);
    }
  mt_gotoXY (0, LOW_OFFSET_Y + 6);
  write (1,
         "└───────────────────────────────────────────────────────────────┘",
         196);
}