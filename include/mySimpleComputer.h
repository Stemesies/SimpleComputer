
#ifndef MY_SIMPLE_COMPUTER_HEADER
#define MY_SIMPLE_COMPUTER_HEADER

#define NULL ((void *)0)

#define STATE_MEMORY_UPDATE 0
#define STATE_ACCUMULATOR_UPDATE 1
#define STATE_INCOUNTER_UPDATE 2
#define STATE_CELL_UPDATE 3
#define STATE_FLAG_UPDATE 4
#define STATE_READ_REQUEST 5
#define STATE_WRITE_REQUEST 6
#define STATE_RESET 7
#define STATE_CPUINFO 8
#define STATE_TICK 9
#define STATE_POST_TICK 10
#define STATE_IS_RUNNING 11

#define REG_ALL 0x1F
// P
#define REG_OVERFLOW 0x1
// 0
#define REG_ZERO_DIV 0x2
// M
#define REG_OUT_OF_BOUNDS 0x4
// T
#define REG_TICK_IGNORE 0x8
// E
#define REG_INVALID_COMMAND 0x10

#define SIGTICK 1
#define SIGRESET 2

#define BITS_PER_COMMAND 7
#define BITS_PER_OPERAND 7
#define BITS_PER_CELL (BITS_PER_COMMAND + BITS_PER_OPERAND + 1)
#define MAX_COMMAND_SIZE 0x7F
#define MAX_OPERAND_SIZE 0x7F
#define MAX_ABSOLUTE_VALUE 0x3FFF
#define MAX_CELL_VALUE 0x7FFF

#define MEMORY_SIZE 128
#define COMMANDS_COUNT 77
#define COMMANDS_COUNT_TRUNCED 16

#define OPNONE 0
#define OPADDR 1

typedef struct _simpleassembly_command
{
  char command[8];
  char code;
  char operandType;
} Command;

Command *sc_getCommands ();

// Аккумулятор

int sc_accumulatorInit ();
int sc_accumulatorGet (int *value);
int sc_accumulatorSet (int value);

// Команды

int sc_commandDecode (int value, int *sign, int *command, int *operand);
int sc_commandEncode (int sign, int command, int operand, int *value);
int sc_commandValidate (int command);

// Счетчик

int sc_incounterInit ();
int sc_incounterGet (int *value);
int sc_incounterSet (int value);

// Регистры флагов

#define sc_regEnable(regs) sc_regSet (regs, regs);
#define sc_regDisable(regs) sc_regSet (regs, 0);

int sc_regInit ();
int sc_regGet (int regaddr, int *value);
int sc_regSet (int regaddr, int value);

// Память

int sc_memoryInit ();
int sc_memoryGet (int address, int *value);
int sc_memorySet (int address, int value);
int sc_memoryLoad (char *filename);
int sc_memorySave (char *filename);

void sc_reset ();

int ALU (int command, int operand);
void CU (int signo);
void ICR (int signo);
void IG_init ();

void sc_setStateListener (int listener (int signal, int value));
int sc_notifyListener (int signal, int value);
void IG_setTickDelay (int delaySec, int delayUsec);
void ICR_tick ();

int sc_tickCounter ();

int sc_isRunning ();

void sc_setSimulationDelay (int sec, int usec);

#endif