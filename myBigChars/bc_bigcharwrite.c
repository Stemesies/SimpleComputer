#include "bc_variables.h"
#include <unistd.h>

int
bc_bigcharwrite (int fd, unsigned char *big, int count)
{

  if (fd < 0 || big == NULL)
    return -1;

  if (count < 0)
    return -2;

  write (fd, big, count * BIGCHAR_HEIGHT * sizeof (unsigned char));
  return 0;
}