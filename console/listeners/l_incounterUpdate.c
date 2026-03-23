#include <console/console.h>
#include <include/myReadKey.h>
#include <include/mySimpleComputer.h>
#include <include/utils.h>

char *
getCurrentCommandName ()
{
  int s, o;
  int command;
  Command *commands = sc_getCommands ();
  sc_incounterGet (&command);
  sc_memoryGet (command, &command);
  sc_commandDecode (command, &s, &command, &o);
  char cmdI[6] = "";
  sprintf (cmdI, "%d ", command);
  write (1, cmdI, 6);
  for (int i = 0; i < COMMANDS_COUNT_TRUNCED; i++)
    {
      if (command == commands[i].code)
        {
          return commands[i].command;
        }
    }
  return "<Command not found>";
}

void
l_incounterUpdate (int idleCounter)
{

  static int tickLast = 0;
  static int incLast = 0;
  static int incThis = 0;

  sc_incounterGet (&incThis);
  if (incLast != incThis)
    {
      incLast = incThis;
      tickLast = sc_tickCounter ();
    }
  mt_gotoXY (3, LOW_OFFSET_Y + 2);
  writef ("TickCounter: %d      ", sc_tickCounter ());

  mt_gotoXY (3, LOW_OFFSET_Y + 3);
  writef ("Current instruction ticks: %d     ", sc_tickCounter () - tickLast);

  mt_gotoXY (3, LOW_OFFSET_Y + 4);
  writef ("Current command: %s Idle: %d      ", getCurrentCommandName (),
          idleCounter);

  printCounters ();
  printCommand ();
  sc_incounterGet (&incounterCell);
  incounterCellIsIdling = idleCounter;

  moveIncounterCell ();
}