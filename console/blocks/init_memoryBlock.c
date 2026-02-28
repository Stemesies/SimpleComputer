#include <console/console.h>
#include <wchar.h>

void
init_memoryBlock ()
{
  mt_gotoXY (0, 0);

  write (1, "┌───────────────────", 61);
  mt_setfgcolor (RED);
  write (1, " Оперативная память ", 38);
  mt_setdefaultcolor ();
  write (1, "────────────────────┐\n", 65);

  for (int i = 2; i < RAM_HEIGHT; i++)
    {
      mt_gotoXY (0, i);
      write (1, "│", 4);
      mt_gotoXY (RAM_WIDTH, i);
      write (1, "│", 4);
    }
  mt_gotoXY (0, RAM_HEIGHT);
  write (1, "└───────────────────────────────────────────────────────────┘\n",
         185);
}