#include "../sc_variables.h"
#include <stdio.h>

int
sc_regInit ()
{
  printf ("RESET\n");
  setFlagRegister (REG_TICK_IGNORE);
}