#include "sc_variables.h"
#include <include/mySimpleComputer.h>
#include <stdio.h>

int signMask = (1 << BITS_PER_COMMAND) << BITS_PER_OPERAND;

void
makeNegative (int *number)
{
  if ((*number & signMask) == 0)
    return;
  *number &= ~signMask;
  *number = ~(*number) + 1;
}

void
returnFromNegative (int *number)
{
  if (*number >= 0)
    return;
  *number = ~((*number) - 1);
  *number |= signMask;
}

int
ALU (int command, int operand)
{
  int operandValue = 0;
  int accumulatorValue = 0;

  if (getIsJustIdleCompleted () == 0)
    {
      incrementIdleIncounter (10);
      return 1;
    }

  if (sc_memoryGet (operand, &operandValue) != 0)
    return -1;

  if (sc_accumulatorGet (&accumulatorValue) != 0)
    return -2;

  makeNegative (&accumulatorValue);
  makeNegative (&operandValue);

  printf ("NEGATIVE accumulator: %d, Operand: %d\n", accumulatorValue,
          operandValue);

  switch (command)
    {
    case 30: // ADD
      accumulatorValue += operandValue;
      break;
    case 31: // SUB
      accumulatorValue -= operandValue;
      break;
    case 32: // DIVIDE
      if (operandValue == 0)
        {
          sc_regSet (REG_ZERO_DIV | REG_TICK_IGNORE,
                     REG_ZERO_DIV | REG_TICK_IGNORE);
          sc_notifyListener (STATE_FLAG_UPDATE, 0);
          return 1;
        }
      accumulatorValue /= operandValue;
      break;
    case 33: // MUL
      accumulatorValue *= operandValue;
      break;
    default:
      return -3;
    }

  printf ("RESULT accumulator: %d, Operand: %d\n\n\n", accumulatorValue,
          operandValue);

  if (accumulatorValue > MAX_ABSOLUTE_VALUE
      || accumulatorValue < -MAX_ABSOLUTE_VALUE)
    {
      sc_regSet (REG_OVERFLOW, REG_OVERFLOW);
      sc_notifyListener (STATE_FLAG_UPDATE, 0);
      return 2;
    }

  returnFromNegative (&accumulatorValue);
  returnFromNegative (&operandValue);

  printf ("accumulator: %d, Operand: %d. MAX: %d\n\n\n", accumulatorValue,
          operandValue, MAX_CELL_VALUE);

  sc_accumulatorSet (accumulatorValue);
  sc_notifyListener (STATE_ACCUMULATOR_UPDATE, 0);

  return 0;
}