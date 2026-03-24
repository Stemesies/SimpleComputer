#include "console.h"
#include "console/console.h"
#include <include/mySimpleComputer.h>
#include <include/myTerm.h>
#include <include/utils.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

char *runOnly = "";

char *testName = "";
int testIndex = 0;
int allowExit = 0;

int initialMemory[MEMORY_SIZE];
int expected[MEMORY_SIZE];

int expectedFlags = 0;
int expectedIncounterPosition = -1;
int expectedAccumulator = 0;
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
  expectedAccumulator = 0;
  expectedFlags = 0;
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
  writef ("Test %d: '%s'", testIndex, testName);

  if (expectedTickCount != -1)
    {
      int accum = sc_tickCounter ();
      if (expectedTickCount != accum)
        {
          mt_setfgcolor (RED);
          writef ("\n | Invalid tick. Expected: %d. Got: %d",
                  expectedTickCount, accum);
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
          writef ("\n | Invalid memory[%d] expected: ", i);
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
    case STATE_POST_TICK:
      animationStep++;
      if (animationStep > 3)
        animationStep = 0;
      // fall through
    case STATE_TICK:;
      if (testFinished)
        break;
      int val = 0;
      sc_incounterGet (&val);
      write (1, "\033[F", 4);
      mt_delline ();
      if (operand > 0)
        {
          mt_setbgcolor (RED);
          mt_setfgcolor (1);
          mt_setfgcolor (BLACK);
          writef ("<blocked %2d>", operand);
          mt_setdefaultcolor ();
          write (1, " ", 1);
        }
      else
        {
          write (1, "             ", 14);
        }
      writef ("[ %d ➜ %d] Test '%s' is running ", sc_tickCounter (), val,
              testName);

      writef ("... %c\n", animation[animationStep]);
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
  sc_setSimulationDelay (0, 25000);
  IG_init ();
  write (1, "\n", 1);

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
    expectedIncounterPosition = 2;
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
    expectedIncounterPosition = 1;
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
    expectedIncounterPosition = 1;
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
    expectedIncounterPosition = 1;
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
    expectedIncounterPosition = 1;
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
    expectedTickCount = 11;
    expectedAccumulator = sencode ("+7f7f");
    expectedIncounterPosition = 0;
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
    expectedTickCount = 11;
    expectedAccumulator = sencode ("-7f7f");
    expectedIncounterPosition = 0;
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
    expectedIncounterPosition = 1;
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
    expectedIncounterPosition = 1;
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
    expectedIncounterPosition = 1;
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
    expectedIncounterPosition = 1;
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
    expectedTickCount = 11;
    expectedAccumulator = sencode ("+7f7f");
    expectedIncounterPosition = 0;
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
    expectedTickCount = 11;
    expectedAccumulator = sencode ("-7f7f");
    expectedIncounterPosition = 0;
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
    expectedIncounterPosition = 1;
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
    expectedIncounterPosition = 1;
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
    expectedIncounterPosition = 1;
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
    expectedIncounterPosition = 1;
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
    expectedAccumulator = 133;
    expectedIncounterPosition = 0;
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
    expectedIncounterPosition = 1;
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
    expectedIncounterPosition = 1;
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
    expectedIncounterPosition = 1;
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
    expectedIncounterPosition = 1;
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
    expectedIncounterPosition = 1;
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
    expectedTickCount = 11;
    expectedAccumulator = sencode ("+7f7f");
    expectedIncounterPosition = 0;
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
    expectedTickCount = 11;
    expectedAccumulator = sencode ("-7f7f");
    expectedIncounterPosition = 0;
    expectedFlags = REG_OVERFLOW;

    sc_accumulatorSet (sencode ("-7f7f"));
    initMemory (0, 0, MUL, 2);
    initMemory (1, 0, HALT, 0);
    sinitMemory (2, "+7f7f");
  });

  /**


  Переходы


  */

  /*
  Проверка на прыжок. Должен перейти в конкретную точку.
  */
  runTest ("JUMP", {
    expectedTickCount = 2;
    expectedIncounterPosition = 3;
    expectedFlags = 0;

    initMemory (0, 0, JUMP, 3);
    initMemory (1, 0, HALT, 0);
    initMemory (3, 0, HALT, 0);
    initMemory (5, 0, HALT, 0);
  });

  /*
  Проверка на условный прыжок. НЕ Должен перейти в конкретную точку.
  */
  runTest ("JNEG", {
    expectedTickCount = 2;
    expectedIncounterPosition = 1;
    expectedFlags = 0;

    initMemory (0, 0, JNEG, 3);
    initMemory (1, 0, HALT, 0);
    initMemory (3, 0, HALT, 0);
    initMemory (5, 0, HALT, 0);
  });

  /*
  Проверка на условный прыжок. НЕ Должен перейти в конкретную точку.
  */
  runTest ("JNEG-Negative", {
    expectedTickCount = 2;
    expectedAccumulator = sencode ("-0010");
    expectedIncounterPosition = 3;
    expectedFlags = 0;

    sc_accumulatorSet (sencode ("-0010"));
    initMemory (0, 0, JNEG, 3);
    initMemory (1, 0, HALT, 0);
    initMemory (3, 0, HALT, 0);
    initMemory (5, 0, HALT, 0);
  });

  /*
  Проверка на условный прыжок. НЕ Должен перейти в конкретную точку.
  */
  runTest ("JZ", {
    expectedTickCount = 2;
    expectedAccumulator = sencode ("+0002");
    expectedIncounterPosition = 1;
    expectedFlags = 0;

    sc_accumulatorSet (sencode ("+0002"));
    initMemory (0, 0, JZ, 3);
    initMemory (1, 0, HALT, 0);
    initMemory (3, 0, HALT, 0);
    initMemory (5, 0, HALT, 0);
  });

  /*
  Проверка на условный прыжок. НЕ Должен перейти в конкретную точку.
  */
  runTest ("JZ-Negative", {
    expectedTickCount = 2;
    expectedAccumulator = sencode ("-0002");
    expectedIncounterPosition = 1;
    expectedFlags = 0;

    sc_accumulatorSet (sencode ("-0002"));
    initMemory (0, 0, JZ, 3);
    initMemory (1, 0, HALT, 0);
    initMemory (3, 0, HALT, 0);
    initMemory (5, 0, HALT, 0);
  });

  /*
  Проверка на условный прыжок. Должен перейти в конкретную точку.
  */
  runTest ("JZ-Zero", {
    expectedTickCount = 2;
    expectedIncounterPosition = 3;
    expectedFlags = 0;

    initMemory (0, 0, JZ, 3);
    initMemory (1, 0, HALT, 0);
    initMemory (3, 0, HALT, 0);
    initMemory (5, 0, HALT, 0);
  });

  /**


  Остальное


  */

  /*
   1 110 0000 100 0000 << 1 = 1 100 0001 000 0001
   28736 << 1 = 24705
  */
  runTest ("RCCR", {
    expectedTickCount = 12;
    expectedAccumulator = 24705;
    expectedFlags = 0;

    sc_accumulatorSet (1);
    initMemory (0, 0, RCCR, 2);
    initMemory (1, 0, HALT, 0);
    dinitMemory (2, 28736);
  });

  /*
   По сути сдвиг не должен быть отрицательным. Так ведь?
  */
  runTest ("RCCR-Negative", {
    expectedTickCount = 11;
    expectedAccumulator = sencode ("-0010");
    expectedFlags = REG_INVALID_COMMAND;

    sc_accumulatorSet (sencode ("-0010"));
    initMemory (0, 0, RCCR, 2);
    initMemory (1, 0, HALT, 0);
    dinitMemory (2, 28736);
  });

  /*
   Раз этот сдвиг циклический, он должен пойти по второму кругу
  */
  runTest ("RCCR-Double", {
    expectedTickCount = 12;
    expectedAccumulator = 24705;
    expectedFlags = 0;

    sc_accumulatorSet (1 + BITS_PER_CELL);
    initMemory (0, 0, RCCR, 2);
    initMemory (1, 0, HALT, 0);
    dinitMemory (2, 28736);
  });

  /*
   Раз этот сдвиг циклический, он должен пойти по третьему кругу

   17 % 7 = 3;
   2 целых круга, сдвиг 3.
   1 110 0000 100 0000 << 3 = 0 000 0100 000 0111
   28736 << 1 = 24705
  */
  runTest ("RCCR-Tripple", {
    expectedTickCount = 12;
    expectedAccumulator = 519;
    expectedFlags = 0;

    sc_accumulatorSet (3 + 2 * BITS_PER_CELL);
    initMemory (0, 0, RCCR, 2);
    initMemory (1, 0, HALT, 0);
    dinitMemory (2, 28736);
  });

  /*
  Если сдвига нет, ничего менять он не должен.
  */
  runTest ("RCCR-Zero", {
    expectedTickCount = 12;
    expectedAccumulator = 28736;
    expectedFlags = 0;

    sc_accumulatorSet (0);
    initMemory (0, 0, RCCR, 2);
    initMemory (1, 0, HALT, 0);
    dinitMemory (2, 28736);
  });

  runTest ("MOVA", {
    expectedTickCount = 22;
    expectedAccumulator = 3;
    expectedFlags = 0;

    sc_accumulatorSet (3);
    initMemory (0, 0, MOVA, 2);
    initMemory (1, 0, HALT, 0);
    dinitMemory (2, 28736);
    expected[3] = 28736;
  });

  runTest ("MOVA-Outbounds", {
    expectedTickCount = 11;
    expectedAccumulator = 129;
    expectedIncounterPosition = 0;
    expectedFlags = REG_OUT_OF_BOUNDS;

    sc_accumulatorSet (129);
    initMemory (0, 0, MOVA, 2);
    initMemory (1, 0, HALT, 0);
    dinitMemory (2, 28736);
  });

  runTest ("MOVA-OutboundsNegative", {
    expectedTickCount = 11;
    expectedAccumulator = sencode ("-0001");
    expectedIncounterPosition = 0;
    expectedFlags = REG_OUT_OF_BOUNDS;

    sc_accumulatorSet (sencode ("-0001"));
    initMemory (0, 0, MOVA, 2);
    initMemory (1, 0, HALT, 0);
    dinitMemory (2, 28736);
  });

  /*


  Готовые программы.


  */

  /*
  for( i in 0 until 5 )
  */
  runTest ("ForLoop", {
    expectedTickCount = 230;
    expectedIncounterPosition = 6;
    expectedFlags = 0;

    // [7] - 1
    // [8] - i
    // [9] - 5

    initMemory (0, 0, LOAD, 8);
    initMemory (1, 0, ADD, 7);
    initMemory (2, 0, STORE, 8);
    initMemory (3, 0, SUB, 9);
    initMemory (4, 0, JZ, 6);
    initMemory (5, 0, JUMP, 0);
    initMemory (6, 0, HALT, 0);
    sinitMemory (7, "+0001");
    expected[8] = sencode ("+0005");
    sinitMemory (9, "+0005");
  });

  return 0;
}
