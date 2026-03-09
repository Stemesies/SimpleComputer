#include <unistd.h>

int
mt_clrscr ()
{
  return write (1, "\033[H\033[2J", 8);
}