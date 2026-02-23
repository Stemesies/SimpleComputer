#include <console/console.h>

void
init_screen ()
{
  mt_clrscr ();
  for (int i = 0; i < SCREEN_HEIGHT; i++)
    {
      putchar ('\n');
    }
}