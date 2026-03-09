#include "../sc_variables.h"

int
sc_regInit ()
{
  setFlagRegister (REG_TICK_IGNORE);
  return 0;
}