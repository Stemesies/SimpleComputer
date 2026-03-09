#include <console/console.h>
#include <include/myReadKey.h>
#include <include/mySimpleComputer.h>
#include <include/myTerm.h>
#include <string.h>
#include <unistd.h>

void
im_memorySave ()
{
  char filename[300] = "";
  write (1, "Введите имя файла для сохранения: ", 63);

  read (0, filename, 299);
  filename[strlen (filename) - 1] = '\0';

  mt_gotoXY (0, COMMAND_LINE_Y);
  mt_delline ();
  switch (sc_memorySave (filename))
    {
    case 0:
      write (1, "Saved successfully.", 20);
      break;
    case -2:
      write (1, "Can't open file. Is path valid?", 32);
      break;
    case -3:
      write (1, "Unexpected I/O error.", 22);
      break;
    }
}
void
im_memoryLoad ()
{
  char filename[300] = "";
  write (1, "Введите имя файла для загрузки: ", 59);

  read (0, filename, 299);
  filename[strlen (filename) - 1] = '\0';

  mt_gotoXY (0, COMMAND_LINE_Y);
  mt_delline ();
  switch (sc_memoryLoad (filename))
    {
    case 0:
      write (1, "Loaded successfully.", 21);
      printMemory ();
      printAccumulator ();
      printCounters ();
      setSelectedCell (getSelectedCell ());
      break;
    case -2:
      write (1, "Can't open file. Is path valid?", 32);
      break;
    case -3:
      write (1, "Unexpected I/O error.", 22);
      break;
    }
}

void
im_reset ()
{
  Keys key = K_0;

  write (1, "Вы действительно хотите сбросить машину? [y/n]\n", 83);
  rk_readkey (&key);
  if (key != 'y' && key != 'Y')
    {
      mt_gotoXY (0, COMMAND_LINE_Y);
      mt_delline ();
      return;
    }
  sc_memoryInit ();
  sc_regInit ();
  sc_accumulatorInit ();
  sc_incounterInit ();
  printMemory ();
  printAccumulator ();
  printCounters ();
  setSelectedCell (getSelectedCell ());
  mt_gotoXY (0, COMMAND_LINE_Y);
  mt_delline ();
}

void
im_exit (int *exitSignal)
{
  Keys key = K_0;

  write (1, "Вы действительно хотите выйти? [y/n]\n", 64);
  rk_readkey (&key);
  if (key != 'y' && key != 'Y')
    {
      mt_gotoXY (0, COMMAND_LINE_Y);
      mt_delline ();
      return;
    }
  *exitSignal = 0;
}