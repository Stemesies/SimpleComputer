#ifndef CONSOLE
#define CONSOLE

#include <include/mySimpleComputer.h>
#include <stdio.h>

#define printInputPointer(prefix) printf (prefix "\033[5m > \033[0m")

#define mScanf(ok, input, onFail)                                             \
  if (1)                                                                      \
    {                                                                         \
      char _m_c = ' ';                                                        \
      if (scanf (ok, input) == 0)                                             \
        onFail;                                                               \
      while ((_m_c = getchar ()) != '\n' && _m_c != EOF)                      \
        {                                                                     \
        }                                                                     \
    }

#define wait() \
if (1)                                                                      \
    {                                                                         \
      printf("\n <Type anything to continue.>\n");\
      char _m_c = ' ';                                                        \
      while ((_m_c = getchar ()) != '\n' && _m_c != EOF)                      \
        {                                                                     \
        }                                                                     \
    }


void cli_flagSubdir ();
int  cli_getFlag ();
void cli_printFlags ();
void cli_setFlag ();

void cli_breakDownCell (int address);
void cli_memorySubdir ();
void cli_printCell (int address);
void cli_printMemory ();
void cli_setMemoryCell ();

void cli_breakdownCommand(int encodedCommand);
void cli_printDecodedCommand (int encodedCommand);

void cli_printMachineStatus();
void cli_setLastCell(int addr);

void cli_setAccumulator ();
void cli_setIncounter ();
#endif