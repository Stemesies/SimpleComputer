#include "bc_variables.h"

int
bc_getbigcharpos (unsigned char *big, int x, int y, int *value)
{

  if (big == 0)
    return -1;

  if (x < 0 || BIGCHAR_WIDTH <= x)
    return -2;

  if (y < 0 || BIGCHAR_HEIGHT <= y)
    return -2;

  *value = (big[y] >> x) & 1;
  return 0;
}