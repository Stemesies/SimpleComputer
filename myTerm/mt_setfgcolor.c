#include <stdio.h>
#include <string.h>
#include <unistd.h>

#include <include/myTerm.h>

int
mt_setfgcolor (Colors color)
{
  if (color <= NOTHING)
    return 0;

  char tmp[14] = { 0 };
  sprintf (tmp, "\033[%dm", color);
  return write (1, tmp, 10);
}