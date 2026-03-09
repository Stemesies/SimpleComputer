#include <string.h>
#include <unistd.h>

int
bc_printA (char *str)
{
  return write (1, str, strlen (str));
}