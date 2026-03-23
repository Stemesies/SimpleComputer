#include <mySimpleComputer/sc_variables.h>

int
sc_commandDecode (int value, int *sign, int *command, int *operand)
{

  if (checkCellOverflow (value))
    return -2;

  if (value == NEGATIVE_ZERO)
    return -5;

  if (operand != NULL)
    *operand = value & MAX_OPERAND_SIZE;

  value >>= BITS_PER_OPERAND;

  if (command != NULL)
    *command = value & MAX_COMMAND_SIZE;

  value >>= BITS_PER_COMMAND;

  if (sign != NULL)
    *sign = value & 0x1;

  return 0;
}