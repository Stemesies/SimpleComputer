#include "bc_variables.h"
#include <include/myBigChars.h>
#include <stdio.h>
#include <unistd.h>

#define printPixel()

int
bc_printbigchar (int big, int x, int y, Colors fg, Colors bg)
{

  unsigned char *chara = getNullChar ();
  int exitCode = 0;

  if (getBigChars () == 0)
    exitCode = -1;

  if (big < 0 || getBigCharsLength () <= big)
    exitCode = -2;

  if (exitCode == 0)
    chara = getBigChar (big);

  mt_setfgcolor (fg);
  mt_setbgcolor (bg);
  mt_alt ();

  int res = 0;

  for (int i = 0; i < BIGCHAR_HEIGHT; i++)
    {
      mt_gotoXY (x, y + i);
      for (int j = 0; j < BIGCHAR_WIDTH; j++)
        {
          bc_getbigcharpos (chara, j, i, &res);
          write (1, res ? "a" : " ", 1);
        }
    }

  mt_dealt ();
  mt_setdefaultcolor ();
  return exitCode;
}