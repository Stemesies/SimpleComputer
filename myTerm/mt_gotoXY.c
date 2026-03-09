#include <stdio.h>
#include <string.h>
#include <unistd.h>

int
mt_gotoXY (int x, int y)
{

  if (0 > x || x >= 1000)
    return -2;
  if (0 > y || y >= 1000)
    return -2;

  char tmp[11] = { 0 };
  sprintf (tmp, "\033[%d;%dH", y, x);
  return write (1, tmp, 11);
}