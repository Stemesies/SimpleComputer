#include "bc_variables.h"
#include <unistd.h>

int
bc_bigcharread (int fd, unsigned char *big, int need_count, int *count)
{

  if (fd == 0 || count == NULL)
    return -1;

  if (need_count <= 0)
    return -2;

  *count
      = read (fd, big, need_count * BIGCHAR_HEIGHT * sizeof (unsigned char));
  *count /= (BIGCHAR_HEIGHT * sizeof (unsigned char));
  return 0;
}