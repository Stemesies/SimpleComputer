#include <console/console.h>

void
cli_printDecodedCommand (int encodedCommand)
{
  int sign = 0;
  int command = 0;
  int operand = 0;

  if (sc_commandDecode (encodedCommand, &sign, &command, &operand) != 0)
    {
      printf ("Invalid cell value: 0x%x.\n", encodedCommand);
      return;
    }

  printf ("%c%02x%02x", sign == 1 ? '-' : '+', command, operand);
}