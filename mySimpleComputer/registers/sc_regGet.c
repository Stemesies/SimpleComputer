#include "../sc_variables.h"

int
sc_regGet (int regaddr, int *value)
{

  /*
  Если указан недопустимый регистр
  и передан неверный указатель на значение,
  то функция завершается со статусом -1.
  */

  // Я надеюсь это опечатка.

  if (value == 0 /* Null */)
    return -1;

  if (regaddr < 0 || regaddr > REG_ALL)
    return -1;

  *value = getFlagRegister () & regaddr;
  return 0;
}