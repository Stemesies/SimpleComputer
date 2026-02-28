#ifndef CONSOLE
#define CONSOLE

#include <include/mySimpleComputer.h>
#include <include/myTerm.h>
#include <stdio.h>
#include <unistd.h>

#define BRD_TOP '─'

// const char *BRD_SIDE = "│"; // { 0xE2, 0x94, 0x82 }; // '│'
#define BRD_TPLFT '┌'
#define BRD_TPRGH '┐'
#define BRD_BTLFT '└'
#define BRD_BTRGH '┘'

#define SCREEN_WIDTH 23 + 23 + 61
#define SCREEN_HEIGHT 15 + 3 + 7 + 1

#define MINI_BLOCK_WIDTH 23
#define MINI_BLOCK_HEIGHT 3

#define RAM_WIDTH 61
#define RAM_HEIGHT 15

#define ACCUMULATOR_OFFSET_X (RAM_WIDTH + 1)
#define FLAGS_OFFSET_X (ACCUMULATOR_OFFSET_X + MINI_BLOCK_WIDTH + 1)

#define DETAILED_CELL_OFFSET_Y (RAM_HEIGHT + 1)
#define INCOUNTER_OFFSET_Y 4

#define TERM_OFFSET_X (RAM_WIDTH + 5)
#define KEYBINDS_OFFSET_X (RAM_WIDTH + 16)
#define LOW_OFFSET_Y (DETAILED_CELL_OFFSET_Y + 3)

void printFlags ();

void printCell (int address, Colors fg, Colors bg);
void printMemory ();

void printCellValue (int encodedCommand, Colors fg, Colors bg);
void printDecodedCommand (int value);

void printAccumulator ();
void printCounters ();

void printBin (int value, int lengthInBits);

void updateTerm ();
void printTerm (int address, int input);

void init_screen ();
void init_memoryBlock ();
void init_accumulatorBlock ();
void init_flagsBlock ();
void init_incounterBlock ();
void init_commandBlock ();
void printCommand ();
void init_detailedCellBlock ();
void init_cacheBlock ();
void init_termBlock ();
void init_keybindsBlock ();

#endif