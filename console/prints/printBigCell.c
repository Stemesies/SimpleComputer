#include <console/console.h>
#include <include/utils.h>

static char buffer[6];

void
printBigCell ()
{
  int offsetX = ACCUMULATOR_OFFSET_X + 3;
  int offsetY = INCOUNTER_OFFSET_Y + 3 + 1;

  int sign = 0;
  int command = 0;
  int operand = 0;

  int cell = 0;

  if (sc_memoryGet (selectedCell, &cell) != 0)
    return;

  if (sc_commandDecode (cell, &sign, &command, &operand) != 0)
    return;

  sprintf (buffer, "%c%02x%02x", sign == 1 ? '-' : '+', command, operand);

  for (int i = 0; i < 5; i++)
    {
      bc_printbigchar (bc_chartoglyph (buffer[i]), offsetX, offsetY, NOTHING,
                       NOTHING);
      offsetX += 8;
    }

  mt_gotoXY (ACCUMULATOR_OFFSET_X + 1, offsetY + 9);
  mt_setfgcolor (BLUE);
  writef ("Номер редактируемой ячейки: %03d", selectedCell);
  mt_setdefaultcolor ();
}