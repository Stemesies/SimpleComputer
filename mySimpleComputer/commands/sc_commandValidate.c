#include <include/mySimpleComputer.h>

int
sc_commandValidate (int value)
{
  if (value < 0 || value > MAX_CELL_VALUE)
    return -2;

  int sign = value >> (BITS_PER_COMMAND + BITS_PER_OPERAND);
  int command = (value >> BITS_PER_OPERAND) & MAX_COMMAND_SIZE;
  if (sign == 0 && command >= COMMANDS_COUNT)
    return -3;

  return 0;
}