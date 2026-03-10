#include <console/console.h>
#include <stdio.h>
#include <string.h>

typedef unsigned char *BigChar;

int
main (int argc, char *argv[])
{
  if (argc < 2)
    {
      write (1, "Usage: font <source> <destination>\n", 36);
      return -1;
    }

  unsigned char *chars = bc_mallocSpace (18);
  if (chars <= (unsigned char *)0)
    {
      mt_setfgcolor (RED);
      write (
          1,
          "Unable to allocate memory for default font. Generation failed.\n",
          64);
      mt_setdefaultcolor ();
      return -1;
    }

  FILE *file = fopen (argv[1], "r");

  if (file == NULL)
    {
      mt_setfgcolor (RED);
      write (1, "Sources not found.\n", 20);
      mt_setdefaultcolor ();
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
  bc_trim (chara);
  int result = bc_save (argv[2]);
  if (result != 0)
    {
      mt_setfgcolor (RED);
      write (1, "Error happened during saving: ", 31);
      char ok[4] = "";
      sprintf (ok, "%d\n", result);
      write (1, ok, 4);

      mt_setdefaultcolor ();
    }
  bc_freeSpace ();

  write (1, "Font generated successfully (◕▿◕✿)\n", 44);
  char buff[31] = "";
  sprintf (buff, "Loaded %d glyphs.\n", chara);
  write (1, buff, strlen (buff));

  return 0;
}