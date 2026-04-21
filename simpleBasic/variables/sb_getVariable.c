#include "../sb_variables.h"

/*
Пытается найти в строке первое упоминание переменной.

Если переменная в строке найдена, метод либо выделяет под нее
память, либо возвращает уже выделенную.
*/

BasicVariable *
sb_getVariable (char *operand)
{
  int oplen = strlen (operand);
  // printf ("Searching variable in '%s'.\n", operand);
  if (*operand - 'A' < 0 || *operand - 'A' > 26)
    {
      int position = 0;
      if (isdigit (*operand))
        printf ("Error at %d: Expected variable. Got number: '", bl);
      else
        printf ("Error at %d: Illegal variable name: '", bl);

      while (isalnum (operand[position]))
        putchar (operand[position++]);
      putchar ('\'');
      putchar ('.');
      putchar ('\n');
      return NULL;
    }

  if (oplen > 2 && isalnum (operand[1]))
    {
      int position = 0;
      printf ("Error at %d: Variable name should be 1 symbol length. Got '",
              bl);
      while (isalnum (operand[position]))
        putchar (operand[position++]);
      putchar ('\'');
      putchar ('.');
      putchar ('\n');

      return NULL;
    }

  BasicVariable *var = definedVariables + (*operand - 'A');
  int definedIn = var->bDefenitionPos - 1;

  if (definedIn == -1)
    {
      var->bDefenitionPos = bp + 1;
      var->aDefenitionPos = MEMORY_SIZE - variablesPoolSize - 1;
      variablesPoolSize++;
      return var;
    }

  return var;
}