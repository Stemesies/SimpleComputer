#include "sc_variables.h"
#include "include/mySimpleComputer.h"

Command commands[] = { { "NOP", 0, OPNONE },     { "CPUINFO", 1, OPNONE },
                       { "READ", 10, OPADDR },   { "WRITE", 11, OPADDR },
                       { "LOAD", 20, OPADDR },   { "STORE", 21, OPADDR },
                       { "ADD", 30, OPADDR },    { "SUM", 31, OPADDR },
                       { "DIVIDE", 32, OPADDR }, { "MUL", 33, OPADDR },
                       { "JUMP", 40, OPADDR },   { "JNEG", 41, OPADDR },
                       { "JZ", 42, OPADDR },     { "HALT", 43, OPNONE },
                       { "RCCR", 70, OPADDR },   { "MOVA", 71, OPADDR } };

int simulatonDelaySecs = 0;
int simulatonDelayUsecs = 500000;
int memory[MEMORY_SIZE];
int flagRegister = REG_TICK_IGNORE;
int accumulator = 0;
int incounter = 0;
int tickCounter = 0;
char idleIncounter = 0;
int isIdleJustCompleted = 0;
int isRunningVar = 0;

int tickCommandStage = 0;
int commandStage = 0;

int
sc_tickCounter ()
{
  return tickCounter;
}

int
sc_isRunning ()
{
  return isRunningVar;
}

Command *
sc_getCommands ()
{
  return commands;
}

void
sc_setSimulationDelay (int sec, int usec)
{
  simulatonDelaySecs = sec;
  simulatonDelayUsecs = usec;
}