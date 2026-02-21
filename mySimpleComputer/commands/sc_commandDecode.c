#include "../sc_variables.h"

int
sc_commandDecode (int value, int *sign, int *command, int *operand)
{

  if (sign == 0 || command == 0 || operand == 0 /* Null */)
    return -1;

  if (value < 0 || value > MAX_CELL_VALUE)
    return -2;

  *operand = value & 0x7F;
  value = value >> BITS_PER_OPERAND;
  *command = value & 0x7F;
  value = value >> BITS_PER_COMMAND;
  *sign = value & 0x1;

  return 0;
}