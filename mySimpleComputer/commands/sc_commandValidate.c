#include "../sc_variables.h"

int
sc_commandValidate (int command)
{
  if (command < 0 || command > MAX_CELL_VALUE)
    return -2;

  if (((command >> BITS_PER_OPERAND) & MAX_COMMAND_SIZE) >= COMMANDS_COUNT)
    return -3;

  return 0;
}