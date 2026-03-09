#include "rk_variables.h"
#include <termios.h>

void
rk_init ()
{
  tcgetattr (1, getCurrentRegime ());
}