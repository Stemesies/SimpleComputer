#include <mySimpleComputer/sc_variables.h>

int
sc_regSet (int regaddr, int value)
{

  if (regaddr < 0 || regaddr > REG_ALL)
    return -1;

  if (value < 0 || value > REG_ALL)
    return -3;

  /*
  Проверяем, если пользователь пытается задать
  значение регистрам, не указанным в regaddr
  */
  if ((value & (~regaddr)) > 0)
    return -2;

  flagRegister = ((flagRegister & (~regaddr)) | value);
  sc_notifyListener (STATE_FLAG_UPDATE, 0);

  return 0;
}
