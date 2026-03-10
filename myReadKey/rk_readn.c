#include <fcntl.h>
#include <include/myReadKey.h>
#include <include/mySimpleComputer.h>
#include <unistd.h>

int
rk_readn (char *buffer, int n)
{
  static Keys key = K_0;

  if (buffer == NULL)
    return -1;

  for (int i = 0; i < n; i++)
    {
      rk_readkey (&key);

      switch (key)
        {
        case K_backspace:
          if (i > 0)
            {
              write (1, "\033[D \033[D", 8);
              i--;
            }
          i--;
          continue;

        case K_esc:
          return 1;

        case K_enter:
          buffer[i] = '\0';
          i = n;
          break;

        default:
          break;
        }

      if (i == n - 1)
        {
          i--;
          continue;
        }

      buffer[i] = key & 255;
      write (1, buffer + i, 1);
    }
  buffer[n - 1] = '\0';

  return 0;
}