#include <console/console.h>
#include <stdio.h>

typedef unsigned char *BigChar;

int
generateDefault ()
{
  bc_freeSpace ();
  unsigned char *chars = bc_mallocSpace (18);

  if (chars <= (unsigned char *)0)
    {
      mt_gotoXY (0, COMMAND_LINE_Y);
      mt_setfgcolor (RED);
      write (1,
             "Unable to allocate memory for default font. Generation failed.",
             63);
      mt_setdefaultcolor ();
      bc_freeSpace ();
      return -1;
    }

  FILE *file = fopen ("../default-font.txt", "r");

  if (file == NULL)
    {
      mt_gotoXY (0, COMMAND_LINE_Y);
      mt_setfgcolor (RED);
      write (1, "No default-font.txt file found.", 32);
      mt_setdefaultcolor ();
      bc_freeSpace ();
      return -1;
    }

  unsigned char bigchar[8] = "";

  int chara = 0;
  int y = 0;
  unsigned char value = 0;

  char buffer[15];
  while (fgets (buffer, 15, file) != NULL)
    {

      if (buffer[0] == '-')
        {
          y = 0;
          bc_setBigChar (chara++, bigchar);
          continue;
        }
      value = 0;

      for (int i = 0; i < 8; i++)
        if (buffer[i] == '#')
          value += (1 << i);

      bigchar[y++] = value;
    }

  fclose (file);

  return 0;
}