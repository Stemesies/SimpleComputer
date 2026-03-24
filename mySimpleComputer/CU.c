#include <mySimpleComputer/sc_variables.h>
#include <signal.h>
#include <unistd.h>

void
CU (int signal)
{
  static int tmpVar;
  static int command;
  static int operand;

  if (signal == SIGUSR1)
    {
      sc_reset ();
      return;
    }

  if (checkAddressOverflow (incounter))
    {
      sc_regEnable (REG_OUT_OF_BOUNDS | REG_TICK_IGNORE);
      return;
    }

  sc_notifyListener (STATE_INCOUNTER_UPDATE, 0);

  sc_memoryGet (incounter, &tmpVar);
  if (sc_commandValidate (memory[incounter]) != 0
      || sc_commandDecode (memory[incounter], NULL, &command, &operand) != 0)
    {
      sc_regEnable (REG_INVALID_COMMAND | REG_TICK_IGNORE);
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
      sc_regEnable (REG_TICK_IGNORE);
      int request = tmpVar == 0 ? operand : -operand;
      if (sc_notifyListener (STATE_READ_REQUEST, request) != 0)
        return;
      break;

    case 11: // WRITE
      sc_mcMemoryGet (operand, NULL);
      sc_notifyListener (STATE_WRITE_REQUEST, operand);
      break;

    case 20: // LOAD
      sc_mcMemoryGet (operand, &tmpVar);
      accumulator = tmpVar;
      sc_notifyListener (STATE_ACCUMULATOR_UPDATE, 0);
      break;

    case 21: // STORE
      sc_mcMemorySet (operand, accumulator);
      sc_notifyListener (STATE_CELL_UPDATE, operand);
      break;

    case 30: // ADD
    case 31: // SUB
    case 32: // DIVIDE
    case 33: // MUL
    case 70: // RCCR
      if (ALU (command, operand) != 0)
        return;
      break;

    case 40: // JUMP
      incounter = operand - 1;
      break;

    case 41: // JNEG
      sc_commandDecode (accumulator, &tmpVar, NULL, NULL);
      if (tmpVar == 1)
        incounter = operand - 1;
      break;

    case 42: // JZ
      if (accumulator == 0)
        incounter = operand - 1;
      break;

    case 43: // HALT
      sc_regEnable (REG_TICK_IGNORE);
      return;

    case 71: // MOVA
      sc_mcMemoryGet (operand, &tmpVar);
      sc_mcMemorySet (accumulator, tmpVar);
      break;
    }
  commandStage = 0;
  incounter++;
  sc_notifyListener (STATE_INCOUNTER_UPDATE, 0);
}