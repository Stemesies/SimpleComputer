#ifndef CONSOLE
#define CONSOLE

#include <include/mySimpleComputer.h>
#include <stdio.h>

void printFlags ();

void printCell (int address);
void printMemory ();

void printCellValue (int encodedCommand);
void printDecodedCommand (int value);

void printAccumulator ();
void printCounters ();

void printBin (int value, int lengthInBits);

#endif