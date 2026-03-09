#include <unistd.h>

int
mt_alt ()
{
  return write (1, "\033(0", 3);
}