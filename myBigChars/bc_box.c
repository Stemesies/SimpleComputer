#include <include/myBigChars.h>
#include <string.h>
#include <unistd.h>

int
bc_box (int x1, int y1, int x2, int y2, Colors box_fg, Colors box_bg,
        char *header, Colors header_fg, Colors header_bg)
{

  if (x2 - x1 < 2 || y2 - y1 < 2)
    return -1;

  if (header == 0)
    return -1;

  if (y1 == 0)
    {
      y1++;
      y2++;
    }

  mt_gotoXY (x1, y1);
  mt_alt ();

  mt_setbgcolor (box_bg);
  mt_setfgcolor (box_fg);

  write (1, "l", 1);
  for (int i = 1; i < x2 - x1 - 1; i++)
    {
      write (1, "q", 1);
    }
  write (1, "k", 1);

  for (int i = 1; i < y2 - y1; i++)
    {
      mt_gotoXY (x1, y1 + i);
      write (1, "x", 1);
      for (int j = 1; j < x2 - x1 - 1; j++)
        {
          write (1, " ", 1);
        }
      write (1, "x", 1);
    }

  mt_gotoXY (x1, y2 - 1);

  write (1, "m", 1);
  for (int i = 1; i < x2 - x1 - 1; i++)
    {
      write (1, "q", 1);
    }
  write (1, "j", 1);

  mt_setdefaultcolor ();

  mt_dealt ();

  int center = x1 + ((x2 - x1) / 2);
  int headerLength = bc_strlen (header);

  mt_gotoXY (center - headerLength / 2, y1);

  mt_setbgcolor (header_bg);
  mt_setfgcolor (header_fg);

  bc_printA (header);
  mt_setdefaultcolor ();
}