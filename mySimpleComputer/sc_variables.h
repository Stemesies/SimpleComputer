#ifndef SC_VARIABLES
#define SC_VARIABLES

#include "../include/mySimpleComputer.h"

#define NEGATIVE_ZERO 16384
#define checkAddressOverflow(address) (address < 0 || MEMORY_SIZE <= address)
#define checkCellOverflow(value) (value < 0 || MAX_CELL_VALUE < value)

#define idleFor(forr)                                                         \
  if (isIdleJustCompleted == 0)                                               \
    {                                                                         \
      idleIncounter = forr;                                                   \
      return;                                                                 \
    }

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

extern int isRunningVar;

int sc_mcMemoryGet (int addr);
int sc_mcMemorySet (int addr, int value);

#endif