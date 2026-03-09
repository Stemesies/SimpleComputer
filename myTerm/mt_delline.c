#include <unistd.h>

int
mt_delline ()
{
  return write (1, "\r\033[2K", 6);
}