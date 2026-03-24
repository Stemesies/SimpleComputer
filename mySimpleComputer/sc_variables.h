#ifndef SC_VARIABLES
#define SC_VARIABLES

#include "../include/mySimpleComputer.h"

#define NEGATIVE_ZERO 16384
#define checkAddressOverflow(address) (address < 0 || MEMORY_SIZE <= address)
#define checkCellOverflow(value) (value < 0 || MAX_CELL_VALUE < value)

extern Command commands[];
extern int simulatonDelaySecs;
extern int simulatonDelayUsecs;
extern int memory[MEMORY_SIZE];
extern int flagRegister;
extern int accumulator;
extern int incounter;

// Счетчик прошедших тактов  с начала запуска.
extern int tickCounter;

// Счетчик простоя процессора
extern char idleIncounter;

// Булевая переменная, обозначающая, что процессор уже простаивал.
extern int isIdleJustCompleted;

/*
В основном нужно, чтобы реализовать последовательный простой процессора.
(Для правильной обработки последовательности команд, требующих простоя)

Представляет собой пройденое кол-во этапов за все время выполнение команды.
*/
extern int commandStage;

/*
Кол-во этапов, пройденное за тик.
*/
extern int tickCommandStage;

extern int isRunningVar;

#define sc_mcMemoryGet(addr, value)                                           \
  if (_sc_mcMemoryGet (addr, value) != 0)                                     \
  return
#define sc_mcMemorySet(addr, value)                                           \
  if (_sc_mcMemorySet (addr, value) != 0)                                     \
  return

int _sc_mcMemoryGet (int addr, int *value);
int _sc_mcMemorySet (int addr, int value);

#endif