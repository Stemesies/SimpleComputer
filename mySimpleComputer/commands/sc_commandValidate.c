#include <include/mySimpleComputer.h>

int
sc_commandValidate (int value)
{
  if (value < 0 || value > MAX_CELL_VALUE)
    return -2;

  int sign = value >> (BITS_PER_COMMAND + BITS_PER_OPERAND);
  int command = (value >> BITS_PER_OPERAND) & MAX_COMMAND_SIZE;

  Command *commands = getCommands ();
  if (sign == 0)
    {
      for (int i = 0; i < COMMANDS_COUNT_TRUNCED; i++)
        if (command == commands[i].code)
          return 0;
      return -3;
    }
  return -1;
}