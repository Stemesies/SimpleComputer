#include "rk_variables.h"
#include <termios.h>

int
rk_mytermregime (int regime, int vtime, int vmin, int echo, int sigint)
{

  struct termios *currentRegime = getCurrentRegime ();
  tcgetattr (0, currentRegime);

  if (regime != 0)
    currentRegime->c_lflag |= ICANON;
  else
    currentRegime->c_lflag &= ~ICANON;

  if (echo != 0)
    currentRegime->c_lflag |= ECHO;
  else
    currentRegime->c_lflag &= ~ECHO;

  // if (sigint != 0)
  //   currentRegime->c_lflag |= ISIG;
  // else
  //   currentRegime->c_lflag &= ~ISIG;

  currentRegime->c_cc[VTIME] = vtime;
  currentRegime->c_cc[VMIN] = vmin;

  tcsetattr (0, TCSANOW, currentRegime);
}
