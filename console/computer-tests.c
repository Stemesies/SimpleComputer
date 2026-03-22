#include "console.h"
#include "console/console.h"
#include <include/mySimpleComputer.h>
#include <include/myTerm.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

char *runOnly = "";

char *testName = "";
int testIndex = 0;
int allowExit = 0;

int initialMemory[MEMORY_SIZE];
int expected[MEMORY_SIZE];

int expectedFlags = -1;
int expectedIncounterPosition = -1;
int expectedAccumulator = -1;
int expectedTickCount = -1;

int testStarted = 0;
int testFinished = 0;

#define dinitMemory(i, decimal)                                               \
  initialMemory[i] = decimal;                                                 \
  expected[i] = initialMemory[i];

#define initMemory(i, sign, command, operand)                                 \
  initialMemory[i] = encode (sign, command, operand);                         \
  expected[i] = initialMemory[i];

#define sinitMemory(i, chara)                                                 \
  initialMemory[i] = sencode (chara);                                         \
  expected[i] = initialMemory[i];

#define print(str, formats...)                                                \
  if (1)                                                                      \
    {                                                                         \
      char amogus[300] = "";                                                  \
      sprintf (amogus, str, formats);                                         \
      write (1, amogus, strlen (amogus));                                     \
    }

int
encode (int sign, int command, int operand)
{
  static int result = 0;
  sc_commandEncode (sign, command, operand, &result);
  return result;
}

int
sencode (char *ok)
{
  char sign;
  int command, operand;
  sscanf (ok, "%c%02x%02x", &sign, &command, &operand);
  sign = sign == '-' ? 1 : 0;
  return encode (sign, command, operand);
}

int
isFlagEnabled (int flag)
{
  static int result = 0;
  sc_regGet (flag, &result);
  return (flag & result) > 0;
}

void
reset ()
{
  for (int i = 0; i < MEMORY_SIZE; i++)
    {
      initialMemory[i] = 0;
      expected[i] = 0;
    }
  expectedTickCount = -1;
  expectedAccumulator = -1;
  expectedFlags = -1;
  expectedIncounterPosition = -1;
  testStarted = 0;
  testFinished = 0;
  allowExit = 0;
  sc_reset ();
}

void
printTestResults ()
{
  int fault = 0;
  print ("Test %d: '%s'", testIndex, testName);

  if (expectedTickCount != -1)
    {
      int accum = sc_tickCounter ();
      if (expectedTickCount != accum)
        {
          mt_setfgcolor (RED);
          print ("\n | Invalid tick. Expected: %d. Got: %d", expectedTickCount,
                 accum);
          mt_setdefaultcolor ();
          fault = 1;
        }
    }

  if (expectedAccumulator != -1)
    {
      int accum = 0;
      sc_accumulatorGet (&accum);
      if (expectedAccumulator != accum)
        {
          mt_setfgcolor (RED);
          write (1, "\n | Invalid accumulator: expected: ", 36);
          printCellValue (expectedAccumulator, NOTHING, NOTHING);
          write (1, " got: ", 7);
          printCellValue (accum, NOTHING, NOTHING);
          mt_setdefaultcolor ();
          fault = 1;
        }
    }
  if (expectedIncounterPosition != -1)
    {
      int accum = 0;
      sc_incounterGet (&accum);
      if (expectedIncounterPosition != accum)
        {
          mt_setfgcolor (RED);
          write (1, "\n | Invalid incounter: expected: ", 34);
          printCellValue (expectedIncounterPosition, NOTHING, NOTHING);
          write (1, " got: ", 7);
          printCellValue (accum, NOTHING, NOTHING);
          mt_setdefaultcolor ();
          fault = 1;
        }
    }
  if (expectedFlags != -1)
    {
      int flags = 0;
      mt_setfgcolor (RED);

      sc_regGet (REG_INVALID_COMMAND, &flags);
      if (flags != (expectedFlags & REG_INVALID_COMMAND))
        {
          if (flags != 0)
            write (1, "\n | Expected REG_INVALID_COMMAND to be 0 ", 42);
          else
            write (1, "\n | Expected REG_INVALID_COMMAND to be 1 ", 42);
          fault = 1;
        }

      sc_regGet (REG_OUT_OF_BOUNDS, &flags);
      if (flags != (expectedFlags & REG_OUT_OF_BOUNDS))
        {
          if (flags != 0)
            write (1, "\n | Expected REG_OUT_OF_BOUNDS to be 0 ", 40);
          else
            write (1, "\n | Expected REG_OUT_OF_BOUNDS to be 1 ", 40);
          fault = 1;
        }

      sc_regGet (REG_OVERFLOW, &flags);
      if (flags != (expectedFlags & REG_OVERFLOW))
        {
          if (flags != 0)
            write (1, "\n | Expected REG_OVERFLOW to be 0 ", 35);
          else
            write (1, "\n | Expected REG_OVERFLOW to be 1 ", 35);
          fault = 1;
        }

      sc_regGet (REG_ZERO_DIV, &flags);
      if (flags != (expectedFlags & REG_ZERO_DIV))
        {
          if (flags != 0)
            write (1, "\n | Expected REG_ZERO_DIV to be 0 ", 35);
          else
            write (1, "\n | Expected REG_ZERO_DIV to be 1 ", 35);
          fault = 1;
        }
      mt_setdefaultcolor ();
    }

  int mem = 0;
  for (int i = 0; i < MEMORY_SIZE; i++)
    {
      sc_memoryGet (i, &mem);
      if (mem != expected[i])
        {
          mt_setfgcolor (RED);
          print ("\n | Invalid memory[%d] expected: ", i);
          printCellValue (expected[i], NOTHING, NOTHING);
          write (1, " got: ", 7);
          printCellValue (mem, NOTHING, NOTHING);
          write (1, "\n", 1);
          mt_setdefaultcolor ();
          fault = 1;
        }
    }
  if (!fault)
    {
      mt_setfgcolor (BRIGHT_GREEN);
      write (1, " Success! (･ω･)b", 21);
      mt_setdefaultcolor ();
    }
  write (1, "\n", 1);
  write (1, "\n", 1);
  allowExit = 1;
}

char animation[4] = { '|', '\\', '-', '/' };
int animationStep = 0;

int
listener (int state, int operand)
{
  switch (state)
    {
    case STATE_FLAG_UPDATE:
      if (!isFlagEnabled (REG_TICK_IGNORE) && testFinished == 0
          && testStarted == 0)

        testStarted = 1;
      else if (isFlagEnabled (REG_TICK_IGNORE) && testStarted == 1
               && testFinished == 0)
        {
          testFinished = 1;
          write (1, "\033[F", 4);
          mt_delline ();
          printTestResults ();
        }
      break;
    case STATE_INCOUNTER_UPDATE:;
      int val = 0;
      sc_incounterGet (&val);
      write (1, "\033[F", 4);
      mt_delline ();
      print ("[ %d ➜ %d] Test '%s' is running (◕‿◕✿) ",
             sc_tickCounter (), val, testName);
      if (operand > 0)
        {
          mt_setbgcolor (RED);
          mt_setfgcolor (1);
          mt_setfgcolor (BLACK);
          print ("<blocked %d >", operand);
          mt_setdefaultcolor ();
          write (1, " ", 1);
        }
      print ("... %c\n", animation[animationStep]);

      animationStep++;
      if (animationStep > 3)
        animationStep = 0;
    }

  return 0;
}

void
test ()
{
  for (int i = 0; i < MEMORY_SIZE; i++)
    sc_memorySet (i, initialMemory[i]);
  testStarted = 0;
  testFinished = 0;
  sc_regSet (REG_TICK_IGNORE, 0);
  listener (STATE_FLAG_UPDATE, 0);
}

/* ------------------------------------------

         Тесты
         Или типа того
         Я не знаю
         ...

------------------------------------------ */

#define runTest(name, amogus)                                                 \
  if (*runOnly == '\0' || strcmp (name, runOnly) == 0)                        \
    {                                                                         \
      reset ();                                                               \
      testIndex++;                                                            \
      testName = name;                                                        \
      if (1)                                                                  \
        amogus;                                                               \
      test ();                                                                \
      while (allowExit != 1)                                                  \
        {                                                                     \
          pause ();                                                           \
        }                                                                     \
      if (*runOnly != '\0')                                                   \
        return 0;                                                             \
    }

#define NOP 0
#define CPUINFO 1
#define READ 10
#define WRITE 11
#define LOAD 20
#define STORE 21
#define ADD 30
#define SUB 31
#define DIVIDE 32
#define MUL 33
#define JUMP 40
#define JNEG 41
#define JZ 42
#define HALT 43
#define RCCR 70
#define MOVA 71

int
main (int argc, char *argv[])
{
  if (argc > 1)
    runOnly = argv[1];

  sc_setStateListener (listener);
  IG_init ();

  runTest ("HALT", {
    expectedTickCount = 1;
    expectedIncounterPosition = 0;

    initMemory (0, 0, HALT, 0);
  });

  runTest ("NOP", {
    expectedTickCount = 2;
    expectedAccumulator = 0;
    expectedFlags = 0;
    expectedIncounterPosition = 1;

    initMemory (0, 0, NOP, 0);
    initMemory (1, 0, HALT, 0);
  });

  /*
  Это, скорее, проверка теста на правильный парсинг команд
  */
  runTest ("MEMORY", {
    expectedTickCount = 1;
    expectedFlags = 0;

    initMemory (0, 0, HALT, 0);
    sinitMemory (1, "+0404");
    expected[1] = encode (0, 4, 4);
  });

  runTest ("MEMORY2", {
    expectedTickCount = 1;
    expectedFlags = 0;

    initMemory (0, 0, HALT, 0);
    dinitMemory (1, 516);
    expected[1] = encode (0, 4, 4);
  });

  /*
  Проверяем на правильную обработку, если выходим из диапазона оперативки
  */
  runTest ("OUT_OF_BOUNDS", {
    expectedTickCount = 1;
    expectedFlags = REG_OUT_OF_BOUNDS;

    sc_incounterSet (244);
    initMemory (0, 0, HALT, 0);
  });

  runTest ("OUT_OF_BOUNDS2", {
    expectedTickCount = 1;
    expectedFlags = REG_OUT_OF_BOUNDS;

    sc_incounterSet (sencode ("-0001"));
    initMemory (0, 0, HALT, 0);
  });

  runTest ("INVALID", {
    expectedTickCount = 1;
    expectedIncounterPosition = 0;
    expectedFlags = REG_INVALID_COMMAND;

    initMemory (0, 1, HALT, 0);
    initMemory (1, 0, HALT, 0);
  });

  /*
  Больше тестов делать нет смысла, т.к. операнд не может
  превышать размер оперативки. Следовательно, нет возможности
  провалить эту операцию.
  */
  runTest ("LOAD", {
    expectedTickCount = 12;
    expectedAccumulator = encode (0, HALT, 0);
    expectedFlags = 0;

    initMemory (0, 0, LOAD, 1);
    initMemory (1, 0, HALT, 0);
  });

  /*
  Больше тестов делать нет смысла, т.к. операнд не может
  превышать размер оперативки. Следовательно, нет возможности
  провалить эту операцию.
  */
  runTest ("STORE", {
    expectedTickCount = 12;
    expectedAccumulator = sencode ("+0404");
    expectedFlags = 0;

    sc_accumulatorSet (sencode ("+0404"));
    initMemory (0, 0, STORE, 2);
    initMemory (1, 0, HALT, 0);
    expected[2] = sencode ("+0404");
  });

  /*
  Простой тест записи в аккумулятор и вывода в ячейку
  */
  runTest ("LOAD&STORE", {
    expectedTickCount = 23;
    expectedAccumulator = encode (0, HALT, 0);
    expectedFlags = 0;

    initMemory (0, 0, LOAD, 2);
    initMemory (1, 0, STORE, 3);
    initMemory (2, 0, HALT, 0);
    expected[3] = encode (0, HALT, 0);
  });

  /**


  Сумма


  */

  /*
  Простейший 1+1.
  */
  runTest ("ADD", {
    expectedTickCount = 12;
    expectedAccumulator = sencode ("+0002");
    expectedFlags = 0;

    sc_accumulatorSet (sencode ("+0001"));
    initMemory (0, 0, ADD, 2);
    initMemory (1, 0, HALT, 0);
    sinitMemory (2, "+0001")
  });

  /*
  Проверка на правильную обработку отрицательных чисел.
  Простейший 1 + (-1).
  */
  runTest ("ADD-Negative", {
    expectedTickCount = 12;
    expectedAccumulator = sencode ("+0000");
    expectedFlags = 0;

    sc_accumulatorSet (sencode ("+0001"));
    initMemory (0, 0, ADD, 2);
    initMemory (1, 0, HALT, 0);
    sinitMemory (2, "-0001");
  });

  /*
  Проверка на правильную обработку отрицательных чисел.
  Простейший -1 + (-1).
  */
  runTest ("ADD-DoubleNegative", {
    expectedTickCount = 12;
    expectedAccumulator = sencode ("-0002");
    expectedFlags = 0;

    sc_accumulatorSet (sencode ("-0001"));
    initMemory (0, 0, ADD, 2);
    initMemory (1, 0, HALT, 0);
    sinitMemory (2, "-0001");
  });

  /*
  Пример более комплексного сложения.
  -2239 + 6033 = 3794
  */
  runTest ("ADD-Complex", {
    expectedTickCount = 12;
    expectedAccumulator = sencode ("+1d52");
    expectedFlags = 0;

    sc_accumulatorSet (sencode ("-113F"));
    initMemory (0, 0, ADD, 2);
    initMemory (1, 0, HALT, 0);
    sinitMemory (2, "+2F11");
  });

  /*
  Проверка на правильную обработку положительного переполнения.
  */
  runTest ("ADD-Overflow", {
    expectedTickCount = 12;
    expectedFlags = REG_OVERFLOW;

    sc_accumulatorSet (sencode ("+7f7f"));
    initMemory (0, 0, ADD, 2);
    initMemory (1, 0, HALT, 0);
    sinitMemory (2, "+0001");
  });

  /*
  Проверка на правильную обработку отрицательного переполнения.
  */
  runTest ("ADD-NegativeOverflow", {
    expectedTickCount = 12;
    expectedFlags = REG_OVERFLOW;

    sc_accumulatorSet (sencode ("-7f7f"));
    initMemory (0, 0, ADD, 2);
    initMemory (1, 0, HALT, 0);
    sinitMemory (2, "-0001");
  });

  /**


  Вычитание


  */

  /*
  Простейший 1-1.
  */
  runTest ("SUB", {
    expectedTickCount = 12;
    expectedAccumulator = sencode ("+0000");
    expectedFlags = 0;

    sc_accumulatorSet (sencode ("+0001"));
    initMemory (0, 0, SUB, 2);
    initMemory (1, 0, HALT, 0);
    sinitMemory (2, "+0001")
  });

  /*
  Проверка на правильную обработку отрицательных чисел.
  Простейший 1 - (-1).
  */
  runTest ("SUB-Negative", {
    expectedTickCount = 12;
    expectedAccumulator = sencode ("+0002");
    expectedFlags = 0;

    sc_accumulatorSet (sencode ("+0001"));
    initMemory (0, 0, SUB, 2);
    initMemory (1, 0, HALT, 0);
    sinitMemory (2, "-0001");
  });

  /*
  Проверка на правильную обработку отрицательных чисел.
  Простейший -1 - (-1).
  */
  runTest ("SUB-DoubleNegative", {
    expectedTickCount = 12;
    expectedAccumulator = sencode ("+0000");
    expectedFlags = 0;

    sc_accumulatorSet (sencode ("-0001"));
    initMemory (0, 0, SUB, 2);
    initMemory (1, 0, HALT, 0);
    sinitMemory (2, "-0001");
  });

  /*
  Пример более комплексного сложения.
  -6033 - 2239 = -8272
  */
  runTest ("SUB-Complex", {
    expectedTickCount = 12;
    expectedAccumulator = sencode ("-4050");
    expectedFlags = 0;

    sc_accumulatorSet (sencode ("-113F"));
    initMemory (0, 0, SUB, 2);
    initMemory (1, 0, HALT, 0);
    sinitMemory (2, "+2F11");
  });

  /*
  Проверка на правильную обработку положительного переполнения.
  */
  runTest ("SUB-Overflow", {
    expectedTickCount = 12;
    expectedFlags = REG_OVERFLOW;

    sc_accumulatorSet (sencode ("+7f7f"));
    initMemory (0, 0, SUB, 2);
    initMemory (1, 0, HALT, 0);
    sinitMemory (2, "-0001");
  });

  /*
  Проверка на правильную обработку отрицательного переполнения.
  */
  runTest ("SUB-NegativeOverflow", {
    expectedTickCount = 12;
    expectedFlags = REG_OVERFLOW;

    sc_accumulatorSet (sencode ("-7f7f"));
    initMemory (0, 0, SUB, 2);
    initMemory (1, 0, HALT, 0);
    sinitMemory (2, "+0001");
  });

  /**


  Деление


  */

  /*
  Простейший 2/2
  */
  runTest ("DIV", {
    expectedTickCount = 12;
    expectedAccumulator = sencode ("+0001");
    expectedFlags = 0;

    sc_accumulatorSet (sencode ("+0002"));
    initMemory (0, 0, DIVIDE, 2);
    initMemory (1, 0, HALT, 0);
    sinitMemory (2, "+0002");
  });

  /*
  Простейший 2/(-2)
  */
  runTest ("DIV-Negative", {
    expectedTickCount = 12;
    expectedAccumulator = sencode ("-0001");
    expectedFlags = 0;

    sc_accumulatorSet (sencode ("+0002"));
    initMemory (0, 0, DIVIDE, 2);
    initMemory (1, 0, HALT, 0);
    sinitMemory (2, "-0002");
  });

  /*
 Простейший (-2)/(-2)
 */
  runTest ("DIV-DoubleNegative", {
    expectedTickCount = 12;
    expectedAccumulator = sencode ("+0001");
    expectedFlags = 0;

    sc_accumulatorSet (sencode ("-0002"));
    initMemory (0, 0, DIVIDE, 2);
    initMemory (1, 0, HALT, 0);
    sinitMemory (2, "-0002");
  });

  /*
  Более сложное деление: 133/(-60) = -2.22
  */
  runTest ("DIV-Complex", {
    expectedTickCount = 12;
    expectedAccumulator = sencode ("-0002");
    expectedFlags = 0;

    sc_accumulatorSet (133);
    initMemory (0, 0, DIVIDE, 2);
    initMemory (1, 0, HALT, 0);
    sinitMemory (2, "-003C");
  });

  /*
  Деление на 0.
  */
  runTest ("DIV-Zero", {
    expectedTickCount = 11;
    expectedFlags = REG_ZERO_DIV;

    sc_accumulatorSet (133);
    initMemory (0, 0, DIVIDE, 2);
    initMemory (1, 0, HALT, 0);
    dinitMemory (2, 0);
  });

  /**


  Умножение


  */

  /*
  Простейший 2*2
  */
  runTest ("MUL", {
    expectedTickCount = 12;
    expectedAccumulator = sencode ("+0004");
    expectedFlags = 0;

    sc_accumulatorSet (sencode ("+0002"));
    initMemory (0, 0, MUL, 2);
    initMemory (1, 0, HALT, 0);
    sinitMemory (2, "+0002");
  });

  /*
  Простейший 2*(-2)
  */
  runTest ("MUL-Negative", {
    expectedTickCount = 12;
    expectedAccumulator = sencode ("-0004");
    expectedFlags = 0;

    sc_accumulatorSet (sencode ("+0002"));
    initMemory (0, 0, MUL, 2);
    initMemory (1, 0, HALT, 0);
    sinitMemory (2, "-0002");
  });

  /*
 Простейший (-2)*(-2)
 */
  runTest ("MUL-DoubleNegative", {
    expectedTickCount = 12;
    expectedAccumulator = sencode ("+0004");
    expectedFlags = 0;

    sc_accumulatorSet (sencode ("-0002"));
    initMemory (0, 0, MUL, 2);
    initMemory (1, 0, HALT, 0);
    sinitMemory (2, "-0002");
  });

  /*
  Более сложное умножение: 21*5 = 105
  */
  runTest ("MUL-Complex", {
    expectedTickCount = 12;
    expectedAccumulator = 105;
    expectedFlags = 0;

    sc_accumulatorSet (21);
    initMemory (0, 0, MUL, 2);
    initMemory (1, 0, HALT, 0);
    dinitMemory (2, 5);
  });

  /*
 Умножение 21*0
 */
  runTest ("MUL-Zero", {
    expectedTickCount = 12;
    expectedAccumulator = 0;
    expectedFlags = 0;

    sc_accumulatorSet (21);
    initMemory (0, 0, MUL, 2);
    initMemory (1, 0, HALT, 0);
    dinitMemory (2, 0);
  });

  /*
  Проверка на правильную обработку положительного переполнения.
  */
  runTest ("MUL-Overflow", {
    expectedTickCount = 12;
    expectedFlags = REG_OVERFLOW;

    sc_accumulatorSet (sencode ("+7f7f"));
    initMemory (0, 0, MUL, 2);
    initMemory (1, 0, HALT, 0);
    sinitMemory (2, "+7f7f");
  });

  /*
  Проверка на правильную обработку отрицательного переполнения.
  */
  runTest ("MUL-NegativeOverflow", {
    expectedTickCount = 12;
    expectedFlags = REG_OVERFLOW;

    sc_accumulatorSet (sencode ("-7f7f"));
    initMemory (0, 0, MUL, 2);
    initMemory (1, 0, HALT, 0);
    sinitMemory (2, "+7f7f");
  });

  return 0;
}
