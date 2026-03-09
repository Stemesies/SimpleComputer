#include "include/mySimpleComputer.h"

int
sc_commandEncode (int sign, int command, int operand, int *value)
{

  if (sign != 0 && sign != 1)
    return -1;

  if (command < 0 || command > MAX_COMMAND_SIZE)
    return -2;

  if (operand < 0 || operand > MAX_OPERAND_SIZE)
    return -3;

  if (value == 0 /* Null */)
    return -4;

  int out = (sign << BITS_PER_COMMAND) | command;
  out = (out << BITS_PER_OPERAND) | operand;

  *value = out;
  return 0;
}