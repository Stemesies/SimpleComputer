#include <console/console.h>

void
cli_setMemoryCell ()
{
  int address = 0;
  int sign = 0;
  int command = 0;
  int operand = 0;

  printInputPointer ("[memory managment] select cell");
  mScanf ("%d", &address, return);

  printInputPointer ("[memory managment] input sign");
  mScanf ("%x", &sign, return);
  printInputPointer ("[memory managment] input command hex");
  mScanf ("%x", &command, return);
  printInputPointer ("[memory managment] input operand hex");
  mScanf ("%x", &operand, return);

  int encodedCommand;
  switch (sc_commandEncode (sign, command, operand, &encodedCommand))
    {
    case -1:
      printf ("Invalid sign. Acceptable: [0;1]\n");
      return;
    case -2:
      printf ("Invalid command. Acceptable: [0x0;0x%x]\n", COMMANDS_COUNT - 1);
      return;
    case -3:
      printf ("Invalid operand. Acceptable: [0x0;0x%x]\n", MAX_OPERAND_SIZE);
      return;
    }

  cli_setLastCell (address);
  switch (sc_memorySet (address, encodedCommand))
    {
    case 0:
      printf ("Successfully updated cell %d.\n", address);
      cli_breakDownCell (address);
      putchar ('\n');
      break;
    case -1:
      printf ("Invalid address: %d.\n", address);
      break;
    case -2:
      printf ("Invalid value: 0x%x.\n", encodedCommand);
      break;
    }
}