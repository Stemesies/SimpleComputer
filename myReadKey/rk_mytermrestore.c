#include "rk_variables.h"

int
rk_mytermrestore ()
{
  struct termios *saved = getSavedRegime ();
  struct termios *current = getCurrentRegime ();

  current->c_iflag = saved->c_iflag;
  current->c_oflag = saved->c_oflag;
  current->c_cflag = saved->c_cflag;
  current->c_lflag = saved->c_lflag;
  current->c_line = saved->c_line;

  for (int i; i < NCCS; i++)
    current->c_cc[i] = saved->c_cc[i];
  tcsetattr (0, TCSANOW, current);
  return 0;
}