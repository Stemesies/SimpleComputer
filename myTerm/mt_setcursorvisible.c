#include <unistd.h>

int
mt_setcursorvisible (int value)
{
  if (value)
    return write (1, "\033[?25h", 7);
  else
    return write (1, "\033[?25l", 7);
}