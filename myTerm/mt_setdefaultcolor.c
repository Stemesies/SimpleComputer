#include <unistd.h>

int
mt_setdefaultcolor ()
{
  return write (1, "\033[0m", 4);
}