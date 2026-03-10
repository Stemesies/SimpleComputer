
#include <fcntl.h>
#include <include/myReadKey.h>
#include <include/mySimpleComputer.h>
#include <stdio.h>
#include <unistd.h>

int
rk_readvalue (int *value, int timeout)
{
  static Keys key = K_0;
  static char buffer[6] = "";

  char sign = 0;
  int command = 0;
  int operand = 0;
  int result = 0;

  write (1, "     \033[5D", 10);
  if (rk_readn (buffer, 6) == 1)
    return 1;

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
