#include "rk_variables.h"
#include <termios.h>

int
rk_mytermsave ()
{
  struct termios *saved = getSavedRegime ();
  struct termios *current = getCurrentRegime ();

  saved->c_iflag = current->c_iflag;
  saved->c_oflag = current->c_oflag;
  saved->c_cflag = current->c_cflag;
  saved->c_lflag = current->c_lflag;
  saved->c_line = current->c_line;

  for (int i; i < NCCS; i++)
    saved->c_cc[i] = current->c_cc[i];
}