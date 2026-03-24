#include <mySimpleComputer/sc_variables.h>

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
    code;                                                                     \
  if (accumulatorValue > MAX_ABSOLUTE_VALUE                                   \
      || accumulatorValue < -MAX_ABSOLUTE_VALUE)                              \
    {                                                                         \
      sc_regEnable (REG_OVERFLOW | REG_TICK_IGNORE);                          \
      return 2;                                                               \
    }                                                                         \
  returnFromNegative (&accumulatorValue);                                     \
  returnFromNegative (&operandValue)

int
ALU (int command, int operand)
{
  int operandValue;
  int accumulatorValue = accumulator;
  sc_mcMemoryGet (operand, &operandValue) 1;

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
            sc_regEnable (REG_ZERO_DIV | REG_TICK_IGNORE);
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
          sc_regEnable (REG_INVALID_COMMAND | REG_TICK_IGNORE);
          return 2;
        }
      accumulatorValue %= BITS_PER_CELL;
      int left = operandValue << accumulatorValue;
      left &= MAX_CELL_VALUE;
      accumulatorValue = operandValue >> (BITS_PER_CELL - accumulatorValue);
      accumulatorValue |= left;
      break;

    default:
      return -3;
    }

  accumulator = accumulatorValue;

  sc_notifyListener (STATE_ACCUMULATOR_UPDATE, 0);

  return 0;
}