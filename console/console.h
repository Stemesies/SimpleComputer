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

#define RAM_COLUMNS 10
#define RAM_ROWS (MEMORY_SIZE / RAM_COLUMNS)
#define RAM_LAST_ROW_LEN (MEMORY_SIZE - RAM_ROWS * RAM_COLUMNS)

#define ACCUMULATOR_OFFSET_X (RAM_WIDTH + 1)
#define FLAGS_OFFSET_X (ACCUMULATOR_OFFSET_X + MINI_BLOCK_WIDTH + 1)

#define INCOUNTER_OFFSET_Y 4

#define TERM_OFFSET_X (RAM_WIDTH + 5)
#define KEYBINDS_OFFSET_X (RAM_WIDTH + 16)
#define LOW_OFFSET_Y (RAM_HEIGHT + 3)

#define COMMAND_LINE_Y (LOW_OFFSET_Y + 7)

extern int selectedCell;
extern int incounterCell;
extern int incounterCellIsIdling;

void printFlags ();

void printCell (int address, Colors fg, Colors bg);
void printMemory ();

void printCellValue (int encodedCommand, Colors fg, Colors bg);
void printDecodedCommand ();

void printAccumulator ();
void printCounters ();

void printBin (int value, int lengthInBits);

void updateTerm ();
int *printTerm (int address, int input);

void init_screen ();
void init_drawIncounterBox (Colors headerColor, Colors backgroundColor);
void init_drawAccumulatorBox (Colors headerColor, Colors backgroundColor);

void printCommand ();

void printBigCell ();

void printIncounterCell ();
void moveIncounterCell ();
void printSelectedCell ();
void hideSelectedCell ();
void moveSelectedCell (int to);

void invalidCellExplain (int resultCode);

// Input managers

void im_memoryLeft ();
void im_memoryRight ();
void im_memoryUp ();
void im_memoryDown ();
void im_editCell ();

void im_accumulator ();
void im_incounter ();

void im_exit (int *exitSignal);
void im_reset ();
void im_memorySave ();
void im_memoryLoad ();

// Listeners

int l_readRequest (int destAddress);
void l_cellUpdate (int cell);
void l_incounterUpdate (int idleCounter);
void l_reset ();

#endif