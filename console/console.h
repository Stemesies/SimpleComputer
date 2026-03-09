#ifndef CONSOLE
#define CONSOLE

#include <include/myBigChars.h>
#include <include/mySimpleComputer.h>
#include <stdio.h>
#include <unistd.h>

#define SCREEN_WIDTH 23 + 23 + 61
#define SCREEN_HEIGHT 15 + 3 + 7 + 1

#define MINI_BLOCK_WIDTH 23
#define MINI_BLOCK_HEIGHT 3

#define RAM_WIDTH 61
#define RAM_HEIGHT 16

#define ACCUMULATOR_OFFSET_X (RAM_WIDTH + 1)
#define FLAGS_OFFSET_X (ACCUMULATOR_OFFSET_X + MINI_BLOCK_WIDTH + 1)

#define INCOUNTER_OFFSET_Y 4

#define TERM_OFFSET_X (RAM_WIDTH + 5)
#define KEYBINDS_OFFSET_X (RAM_WIDTH + 16)
#define LOW_OFFSET_Y (RAM_HEIGHT + 3)

#define COMMAND_LINE_Y (LOW_OFFSET_Y + 7)

void printFlags ();

void printCell (int address, Colors fg, Colors bg);
void printMemory ();

void printCellValue (int encodedCommand, Colors fg, Colors bg);
void printDecodedCommand ();

void printAccumulator ();
void printCounters ();

void printBin (int value, int lengthInBits);

void updateTerm ();
void printTerm (int address, int input);

void init_screen ();

void printCommand ();

void printBigCell ();

int getSelectedCell ();

void setSelectedCell (int addr);
#endif