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

static int memory[MEMORY_SIZE];

static int flagRegister = REG_TICK_IGNORE;
static int accumulator = 0;
static int incounter = 0;
static char idleIncounter = 0;
static int tickCounter = 0;
static int isIdleJustCompleted = 0;

int *
getMemory ()
{
  return memory;
}

int
getFlagRegister ()
{
  return flagRegister;
}

void
setFlagRegister (int value)
{
  flagRegister = value;
}

int
getAccumulator ()
{
  return accumulator;
}

void
setAccumulator (int value)
{
  accumulator = value;
}

int
getIncounter ()
{
  return incounter;
}

void
setIncounter (int value)
{
  incounter = value;
}

int
sc_tickCounter ()
{
  return tickCounter;
}

void
incrementTickCounter ()
{
  tickCounter++;
}

void
resetTickCounter ()
{
  tickCounter = 0;
}

char
getIdleIncounter ()
{
  return idleIncounter;
}

void
decrementIdleIncounter ()
{
  idleIncounter--;
}

void
incrementIdleIncounter (char value)
{
  idleIncounter += value;
}

int
getIsJustIdleCompleted ()
{
  return isIdleJustCompleted;
}
void
setIsJustIdleCompleted (int value)
{
  isIdleJustCompleted = value;
}

Command *
getCommands ()
{

  return commands;
}