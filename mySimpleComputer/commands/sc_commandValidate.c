#include <mySimpleComputer/sc_variables.h>

int
sc_commandValidate (int value)
{
  if (checkCellOverflow (value))
    return -2;

  int sign = value >> (BITS_PER_COMMAND + BITS_PER_OPERAND);
  int command = (value >> BITS_PER_OPERAND) & MAX_COMMAND_SIZE;

  if (sign != 0)
    return -1;

  for (int i = 0; i < COMMANDS_COUNT_TRUNCED; i++)
    if (command == commands[i].code)
      return 0;
  return -3;
}