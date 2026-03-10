#include "include/myTerm.h"
#include <console/console.h>
#include <unistd.h>

void
init_screen ()
{
  for (int i = 0; i < SCREEN_HEIGHT * 2; i++)
    write (1, "\n", 2);
  mt_clrscr ();
  mt_gotoXY (0, 0);

  bc_box (0, 0, RAM_WIDTH, RAM_HEIGHT - 1, NOTHING, NOTHING,
          " Оперативная память ", RED, NOTHING);

  bc_box (ACCUMULATOR_OFFSET_X, 0, ACCUMULATOR_OFFSET_X + MINI_BLOCK_WIDTH, 3,
          NOTHING, NOTHING, " Аккумулятор ", RED, NOTHING);

  bc_box (FLAGS_OFFSET_X, 0, FLAGS_OFFSET_X + MINI_BLOCK_WIDTH, 3, NOTHING,
          NOTHING, " Регистр  флагов ", RED, NOTHING);

  bc_box (ACCUMULATOR_OFFSET_X, INCOUNTER_OFFSET_Y,
          ACCUMULATOR_OFFSET_X + MINI_BLOCK_WIDTH, INCOUNTER_OFFSET_Y + 3,
          NOTHING, NOTHING, " Счетчик  команд ", RED, NOTHING);

  bc_box (FLAGS_OFFSET_X, INCOUNTER_OFFSET_Y,
          FLAGS_OFFSET_X + MINI_BLOCK_WIDTH, INCOUNTER_OFFSET_Y + 3, NOTHING,
          NOTHING, " Команда ", RED, NOTHING);

  bc_box (ACCUMULATOR_OFFSET_X, INCOUNTER_OFFSET_Y + 3,
          ACCUMULATOR_OFFSET_X + MINI_BLOCK_WIDTH + MINI_BLOCK_WIDTH + 1,
          RAM_HEIGHT + 3, NOTHING, NOTHING,
          " Редактируемая ячейка (увеличено) ", RED, NOTHING);

  bc_box (0, RAM_HEIGHT, 61, RAM_HEIGHT + 3, NOTHING, NOTHING,
          " Редактируемая ячейка (формат) ", RED, NOTHING);

  bc_box (0, LOW_OFFSET_Y, 65, LOW_OFFSET_Y + 7, NOTHING, NOTHING,
          " Кеш процессора ", GREEN, NOTHING);

  bc_box (TERM_OFFSET_X, LOW_OFFSET_Y, TERM_OFFSET_X + 11, LOW_OFFSET_Y + 7,
          NOTHING, NOTHING, " IN--OUT ", GREEN, NOTHING);

  bc_box (KEYBINDS_OFFSET_X, LOW_OFFSET_Y, KEYBINDS_OFFSET_X + 32,
          LOW_OFFSET_Y + 7, NOTHING, NOTHING, " Клавиши ", GREEN, NOTHING);

  mt_gotoXY (KEYBINDS_OFFSET_X + 1, LOW_OFFSET_Y + 1);
  write (1, "l - load  s - save  i - reset", 30);
  mt_gotoXY (KEYBINDS_OFFSET_X + 1, LOW_OFFSET_Y + 2);
  write (1, "r - run  t - step", 18);
  mt_gotoXY (KEYBINDS_OFFSET_X + 1, LOW_OFFSET_Y + 3);
  write (1, "ESC - выход", 17);
  mt_gotoXY (KEYBINDS_OFFSET_X + 1, LOW_OFFSET_Y + 4);
  write (1, "F5 - accumulator", 17);
  mt_gotoXY (KEYBINDS_OFFSET_X + 1, LOW_OFFSET_Y + 5);
  write (1, "F6 - instruction counter", 25);
  mt_gotoXY (KEYBINDS_OFFSET_X + 1, LOW_OFFSET_Y + 6);
}