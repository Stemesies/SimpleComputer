#include <stdio.h>
#include <string.h>
#include <unistd.h>

#include <include/myTerm.h>

int
mt_setbgcolor (enum colors color)
{
  if (color <= NOTHING)
    return 0;

  char tmp[14] = { 0 };
  sprintf (tmp, "\033[%dm", color + 10);
  return write (1, tmp, 10);
}