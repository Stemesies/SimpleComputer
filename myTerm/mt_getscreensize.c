#include <stdio.h>
#include <sys/ioctl.h>
#include <termios.h>

static struct winsize ws;

int
mt_getscreensize (int *rows, int *columns)
{
  if (ioctl (fileno (stdout), TIOCGWINSZ, &ws) != 0)
    {
      *rows = 24;
      *columns = 80;
      return -1;
    }

  *rows = ws.ws_row;
  *columns = ws.ws_col;
  return 0;
}