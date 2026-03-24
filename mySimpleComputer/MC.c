#include "include/mySimpleComputer.h"
#include <mySimpleComputer/sc_variables.h>
#include <unistd.h>

int size = 0;

int
_sc_mcMemoryGet (int address, int *value)
{

  if (checkAddressOverflow (address))
    {
      sc_regEnable (REG_OUT_OF_BOUNDS | REG_TICK_IGNORE);
      return -1;
    }

  if (commandStage <= tickCommandStage && !isIdleJustCompleted)
    {
      idleIncounter += 10;
      return 1;
    }
  isIdleJustCompleted = 0;
  tickCommandStage++;

  if (value != NULL)
    *value = memory[address];
  return 0;
}

int
_sc_mcMemorySet (int address, int value)
{

  if (checkAddressOverflow (address))
    {
      sc_regEnable (REG_OUT_OF_BOUNDS | REG_TICK_IGNORE);
      return -1;
    }

  if (checkCellOverflow (value))
    {
      sc_regEnable (REG_OVERFLOW | REG_TICK_IGNORE);
      return -2;
    }

  if (commandStage <= tickCommandStage && !isIdleJustCompleted)
    {
      idleIncounter += 10;
      return 1;
    }
  isIdleJustCompleted = 0;
  tickCommandStage++;

  memory[address] = value;
  return 0;
}
