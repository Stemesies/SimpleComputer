#include "mySimpleComputer/sc_variables.h"
#include <include/mySimpleComputer.h>
#include <signal.h>
#include <unistd.h>

static int currentInstruction;
static int sign;
static int command;
static int operand;
static int tmpVar;

void
CU (int signal)
{
  if (signal == SIGUSR1)
    {
      sc_reset ();
      return;
    }

  sc_incounterGet (&currentInstruction);
  if (currentInstruction >= MEMORY_SIZE)
    {
      sc_regSet (REG_OUT_OF_BOUNDS | REG_TICK_IGNORE,
                 REG_OUT_OF_BOUNDS | REG_TICK_IGNORE);
      return;
    }

  sc_notifyListener (STATE_INCOUNTER_UPDATE, 0);

  sc_memoryGet (currentInstruction, &tmpVar);
  if (sc_commandValidate (tmpVar) != 0
      || sc_commandDecode (tmpVar, &sign, &command, &operand) != 0)
    {
      sc_regSet (REG_INVALID_COMMAND | REG_TICK_IGNORE,
                 REG_INVALID_COMMAND | REG_TICK_IGNORE);
      return;
    }

  switch (command)
    {
    case 0: // NOP
      break;
    case 1: // CPUINFO
      sc_notifyListener (STATE_CPUINFO, 0);
      break;
    case 10: // READ
      sc_regGet (REG_TICK_IGNORE, &tmpVar);
      sc_regSet (REG_TICK_IGNORE, REG_TICK_IGNORE);
      if (tmpVar == 0)
        {
          if (sc_notifyListener (STATE_READ_REQUEST, operand) != 0)
            return;
        }
      else
        {
          if (sc_notifyListener (STATE_READ_REQUEST, -operand) != 0)
            return;
        }
      break;
    case 11: // WRITE
      if (getIsJustIdleCompleted () == 0)
        {
          incrementIdleIncounter (10);
          return;
        }
      sc_notifyListener (STATE_WRITE_REQUEST, operand);
      break;
    case 20: // LOAD
      if (getIsJustIdleCompleted () == 0)
        {
          incrementIdleIncounter (10);
          return;
        }
      sc_memoryGet (operand, &tmpVar);
      sc_accumulatorSet (tmpVar);
      sc_notifyListener (STATE_ACCUMULATOR_UPDATE, 0);
      break;
    case 21: // STORE
      if (getIsJustIdleCompleted () == 0)
        {
          incrementIdleIncounter (10);
          return;
        }
      sc_accumulatorGet (&tmpVar);
      sc_memorySet (operand, tmpVar);
      sc_notifyListener (STATE_CELL_UPDATE, operand);
      break;
    case 30: // ADD
    case 31: // SUB
    case 32: // DIVIDE
    case 33: // MUL
    case 70: // RCCR
      if (ALU (command, operand) == 1)
        return;
      break;
    case 40: // JUMP
      currentInstruction = operand - 1;
      break;
    case 41: // JNEG
      sc_accumulatorGet (&tmpVar);
      sc_commandDecode (tmpVar, &tmpVar, &command, &command);
      if (tmpVar == 1)
        currentInstruction = operand - 1;
      break;
    case 42: // JZ
      sc_accumulatorGet (&tmpVar);
      if (tmpVar == 0)
        currentInstruction = operand - 1;
      break;
    case 43: // HALT
      sc_regSet (REG_TICK_IGNORE, REG_TICK_IGNORE);
      return;
    case 71: // MOVA
      if (getIsJustIdleCompleted () == 0)
        {
          incrementIdleIncounter (20);
          return;
        }
      int source;
      sc_memoryGet (operand, &source);
      sc_accumulatorGet (&tmpVar);
      if (sc_memorySet (tmpVar, source) == -1)
        {
          sc_regSet (REG_OUT_OF_BOUNDS | REG_TICK_IGNORE,
                     REG_OUT_OF_BOUNDS | REG_TICK_IGNORE);
          return;
        }
      break;
    }

  sc_incounterSet (currentInstruction + 1);
  sc_notifyListener (STATE_INCOUNTER_UPDATE, 0);
}