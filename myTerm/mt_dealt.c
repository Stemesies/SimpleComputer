#include <unistd.h>

int
mt_dealt ()
{
  return write (1, "\033(B", 3);
}