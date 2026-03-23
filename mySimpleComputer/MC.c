#include "include/mySimpleComputer.h"
#include <mySimpleComputer/sc_variables.h>
#include <unistd.h>

int size = 0;

int
sc_mcMemoryGet (int address)
{

  if (checkAddressOverflow (address))
    {
      sc_regEnable (REG_OUT_OF_BOUNDS | REG_TICK_IGNORE);
      return -1;
    }

  //   for (int i = 0; i < 10; i++)
  //       pause ();

  return memory[address];
}

int
sc_mcMemorySet (int address, int value)
{

  if (checkAddressOverflow (address))
    {
      sc_regEnable (REG_OUT_OF_BOUNDS | REG_TICK_IGNORE);
      return -1;
    }

  if (checkCellOverflow (value))
    {
      sc_regEnable (REG_OVERFLOW | REG_TICK_IGNORE);
      return -1;
    }

  //   for (int i = 0; i < 10; i++)
  //     pause ();

  memory[address] = value;
  return 0;
}
