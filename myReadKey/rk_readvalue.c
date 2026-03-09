
#include <include/myReadKey.h>
#include <include/mySimpleComputer.h>
#include <stdio.h>
#include <unistd.h>

Keys key = K_0;
char buffer[6] = "";
int
rk_readvalue (int *value, int timeout)
{

  char sign = 0;
  int command = 0;
  int operand = 0;
  int result = 0;

  rk_mytermsave ();
  rk_mytermregime (1, timeout, 5, 1, 1);

  write (1, "     \033[5D", 10);

  for (int i = 0; i < 6; i++)
    {
      rk_readkey (&key);

      if (key == K_backspace)
        {
          if (i > 0)
            {
              write (1, "\033[D \033[D", 8);
              i--;
            }
          i--;
          continue;
        }

      if (key == K_esc)
        return 1;

      if (key == K_enter)
        {
          buffer[i] = '\0';
          break;
        }
      if (i == 5)
        {
          i--;
          continue;
        }

      buffer[i] = key & 255;
      write (1, buffer + i, 1);
    }

  // read (1, &buffer, 6 * sizeof (char));
  buffer[5] = '\0';
  if (sscanf (buffer, "%c%02x%02x", &sign, &command, &operand) < 3)
    return -20;

  if (sign != '+' && sign != '-')
    return -10;

  int encodeResult = sc_commandEncode (sign == '-', command, operand, &result);
  if (encodeResult != 0)
    return encodeResult;

  if (sc_commandValidate (result) != 0)
    {
      return -11;
    }
  *value = result;

  rk_mytermrestore ();
  return 0;
}
