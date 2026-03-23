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

#define withNegative(code)                                                    \
  makeNegative (&accumulatorValue);                                           \
  makeNegative (&operandValue);                                               \
  if (1)                                                                      \
    code if (accumulatorValue > MAX_ABSOLUTE_VALUE                            \
             || accumulatorValue < -MAX_ABSOLUTE_VALUE)                       \
    {                                                                         \
      sc_regSet (REG_OVERFLOW | REG_TICK_IGNORE,                              \
                 REG_OVERFLOW | REG_TICK_IGNORE);                             \
      return 2;                                                               \
    }                                                                         \
  returnFromNegative (&accumulatorValue);                                     \
  returnFromNegative (&operandValue)

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

  switch (command)
    {
    case 30: // ADD
      withNegative ({ accumulatorValue += operandValue; });
      break;
    case 31: // SUB
      withNegative ({ accumulatorValue -= operandValue; });
      break;
    case 32: // DIVIDE
      withNegative ({
        if (operandValue == 0)
          {
            sc_regSet (REG_ZERO_DIV | REG_TICK_IGNORE,
                       REG_ZERO_DIV | REG_TICK_IGNORE);
            return 1;
          }
        accumulatorValue /= operandValue;
      });
      break;
    case 33: // MUL
      withNegative ({ accumulatorValue *= operandValue; });
      break;
    case 70: // RCCR
      if ((accumulatorValue & signMask) > 0)
        {
          sc_regSet (REG_INVALID_COMMAND | REG_TICK_IGNORE,
                     REG_INVALID_COMMAND | REG_TICK_IGNORE);
          return 2;
        }
      accumulatorValue %= BITS_PER_CELL;
      printf ("BEFORE accumulator: %d, Operand: %d\n", accumulatorValue,
              operandValue);
      int left = operandValue << accumulatorValue;
      left &= MAX_CELL_VALUE;
      printf ("LEFT: %d\n", left);
      accumulatorValue = operandValue >> (BITS_PER_CELL - accumulatorValue);
      printf ("RIGHT: %d\n", accumulatorValue);
      accumulatorValue = (left | accumulatorValue);
      sc_accumulatorSet (accumulatorValue);
      printf ("RESULT: %d\n\n\n", accumulatorValue);
      break;
    default:
      return -3;
    }

  printf ("accumulator: %d, Operand: %d. MAX: %d\n\n\n", accumulatorValue,
          operandValue, MAX_CELL_VALUE);

  sc_accumulatorSet (accumulatorValue);
  sc_notifyListener (STATE_ACCUMULATOR_UPDATE, 0);

  return 0;
}