
#ifndef MY_SIMPLE_COMPUTER_HEADER
#define MY_SIMPLE_COMPUTER_HEADER

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

#define BITS_PER_COMMAND 7
#define BITS_PER_OPERAND 7
#define MAX_COMMAND_SIZE 0x7F
#define MAX_OPERAND_SIZE 0x7F
#define MAX_CELL_VALUE 0x7FFF

#define MEMORY_SIZE 128
#define COMMANDS_COUNT 77

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
int sc_regInit ();
int sc_regGet (int regaddr, int *value);
int sc_regSet (int regaddr, int value);

// Память

int sc_memoryInit ();
int sc_memoryGet (int address, int *value);
int sc_memorySet (int address, int value);
int sc_memoryLoad (char *filename);
int sc_memorySave (char *filename);

#endif