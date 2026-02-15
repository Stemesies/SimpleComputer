#include "sc_variables.h"

static int memory[MEMORY_SIZE];

static int flagRegister = REG_TICK_IGNORE;
static int accumulator = 0;
static int incounter = 0;

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