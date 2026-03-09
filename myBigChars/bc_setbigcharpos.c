#include "bc_variables.h"

int
bc_setbigcharpos (unsigned char *big, int x, int y, int value)
{

  if (big == 0)
    return -1;

  if (x < 0 || BIGCHAR_WIDTH <= x)
    return -2;

  if (y < 0 || BIGCHAR_HEIGHT <= y)
    return -2;

  if (value == 0)
    big[y] = (big[y] & (~(1 << x)));
  else
    big[y] = (big[y] | (1 << x));

  return 0;
}