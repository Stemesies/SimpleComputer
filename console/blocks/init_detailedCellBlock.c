#include <console/console.h>

void
init_detailedCellBlock ()
{
  mt_gotoXY (0, DETAILED_CELL_OFFSET_Y);

  write (1, "┌──────────────", 46);
  mt_setfgcolor (RED);
  mt_setbgcolor (WHITE);
  write (1, " Редактируемая ячейка (формат) ", 57);
  mt_setdefaultcolor ();
  write (1, "──────────────┐", 46);

  mt_gotoXY (0, DETAILED_CELL_OFFSET_Y + 1);
  write (1, "│ ", 5);
  mt_gotoXY (RAM_WIDTH - 1, DETAILED_CELL_OFFSET_Y + 1);
  write (1, " │", 5);

  mt_gotoXY (0, DETAILED_CELL_OFFSET_Y + 2);
  write (1, "└───────────────────────────────────────────────────────────┘\n",
         185);
}