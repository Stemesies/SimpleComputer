#include <mySimpleComputer/sc_variables.h>

int
sc_regGet (int regaddr, int *value)
{

  if (value == NULL)
    return -1;

  if (regaddr < 0 || regaddr > REG_ALL)
    return -1;

  *value = flagRegister & regaddr;
  return 0;
}