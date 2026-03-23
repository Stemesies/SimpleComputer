#include <console/console.h>
#include <include/myReadKey.h>
#include <include/myTerm.h>
#include <signal.h>

void
im_memorySave ()
{
  char filename[300] = "";
  mt_delline ();
  write (1, "Введите имя файла для сохранения: ", 63);

  if (rk_readn (filename, 300) == 1)
    {
      mt_delline ();
      return;
    }

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
  mt_delline ();
  write (1, "Введите имя файла для загрузки: ", 59);

  if (rk_readn (filename, 300) == 1)
    {
      mt_delline ();
      return;
    }

  mt_gotoXY (0, COMMAND_LINE_Y);
  mt_delline ();
  switch (sc_memoryLoad (filename))
    {
    case 0:
      write (1, "Loaded successfully.", 21);
      l_reset ();
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

  mt_gotoXY (0, COMMAND_LINE_Y);
  mt_delline ();
  write (1, "Вы действительно хотите сбросить машину? [y/n]", 82);

  rk_readkey (&key);
  mt_delline ();
  if (key != 'y' && key != 'Y')
    return;
  raise (SIGUSR1);
}

void
im_exit (int *exitSignal)
{
  Keys key = K_0;

  mt_delline ();
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