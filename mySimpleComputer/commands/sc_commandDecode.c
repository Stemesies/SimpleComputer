#include <include/mySimpleComputer.h>

int
sc_commandDecode (int value, int *sign, int *command, int *operand)
{

  if (sign == (int *)0 || command == (int *)0 || operand == (int *)0)
    return -1;

  if (value < 0 || value > MAX_CELL_VALUE)
    return -2;

  *operand = value & MAX_OPERAND_SIZE;
  value = value >> BITS_PER_OPERAND;
  *command = value & MAX_COMMAND_SIZE;
  value = value >> BITS_PER_COMMAND;
  *sign = value & 0x1;

  return 0;
}