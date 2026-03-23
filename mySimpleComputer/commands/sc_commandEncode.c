#include <mySimpleComputer/sc_variables.h>

int
sc_commandEncode (int sign, int command, int operand, int *value)
{

  if (sign != 0 && sign != 1)
    return -1;

  if (command < 0 || command > MAX_COMMAND_SIZE)
    return -2;

  if (operand < 0 || operand > MAX_OPERAND_SIZE)
    return -3;

  if (value == NULL)
    return -4;

  int out = (sign << BITS_PER_COMMAND) | command;
  out = (out << BITS_PER_OPERAND) | operand;

  if (out == NEGATIVE_ZERO)
    return -5;

  *value = out;
  return 0;
}