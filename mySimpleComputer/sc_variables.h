#ifndef SC_VARIABLES
#define SC_VARIABLES

#include "../include/mySimpleComputer.h"

int *getMemory ();

int getFlagRegister ();
void setFlagRegister (int value);

int getAccumulator ();
void setAccumulator (int value);

int getIncounter ();
void setIncounter (int value);

#endif