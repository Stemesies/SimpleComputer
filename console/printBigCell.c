#include <console/console.h>

static char buffer[6];
static char buffer2[57];
static char *render;

void
printBigCell ()
{
  int offsetX = ACCUMULATOR_OFFSET_X + 3;
  int offsetY = INCOUNTER_OFFSET_Y + 3 + 1;

  int sign = 0;
  int command = 0;
  int operand = 0;

  int cell = 0;

  if (sc_memoryGet (getSelectedCell (), &cell) != 0)
    return;

  if (sc_commandDecode (cell, &sign, &command, &operand) != 0)
    return;

  sprintf (buffer, "%c%02x%02x", sign == 1 ? '-' : '+', command, operand);

  render = buffer;
  for (int i = 0; i < 5; i++)
    {
      bc_printbigchar (bc_chartoglyph (render[i]), offsetX, offsetY, NOTHING,
                       NOTHING);
      offsetX += 8;
    }

  mt_gotoXY (ACCUMULATOR_OFFSET_X + 1, offsetY + 9);
  mt_setfgcolor (BLUE);
  sprintf (buffer2, "Номер редактируемой ячейки: %03d", getSelectedCell ());
  write (1, buffer2, 57);
  mt_setdefaultcolor ();
}